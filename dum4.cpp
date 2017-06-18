/*
 * Dum 4 - pseudographical 3D-action
 * Copyright (C) 2005-2010 Kurashov Artem Konstantinovich
 * 
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

#include <iostream>
#include "tride.hpp"
#include <cstdlib>
#include <ctime>

std::string real_name (int object_id)
{

  switch (object_id)
    {
    case 0:
      return "|######|";
    case 1:
      return "o00";
    case 2:
      return "o0_0_0o";
    case 3:
      return "/-0|0-\\";
    case 4:
      return "|_=====_|";
    case 5:
      return "|##|    |##|";
    case 6:
      return "|=======|";
    case 7:
      return "|+|";
    case 8:
      return "UUUU";
    case 9:
      return "/\\";
    case 10:
      return "|exit|";
    case 11:
      return "*";
    default:
      return "      ";
    }
}

int
map_random ()
{
  return 1 + (int) (9.0 * rand () / (RAND_MAX + 1.0));
}

int
main ()
{
  map_engine *map1;
  eyesviewlfr image1;
  int i, j, k;
  int emove, tty_in, health, armour, bullets;
  int imap_size[3], st_coord[3], ex_coord[3], st_angle;
  srand (time (0));
  imap_size[0] = (int) (50.0 * rand () / (RAND_MAX + 1.0));
  imap_size[1] = (int) (50.0 * rand () / (RAND_MAX + 1.0));
  imap_size[2] = (int) (10.0 * rand () / (RAND_MAX + 1.0));
  st_coord[0] = imap_size[0] / 2;
  st_coord[1] = imap_size[1] / 2;
  st_coord[2] = imap_size[2] - 1;
  ex_coord[0] = 1;		
  ex_coord[1] = 1;	
  ex_coord[2] = 0;
  st_angle = (int) (4.0 * rand () / (RAND_MAX + 1.0));
  health = 100;
  armour = 0;
  bullets = 50;
  map1 =
    new map_engine (imap_size[0], imap_size[1], imap_size[2], st_coord[0],
		    st_coord[1], st_coord[2], st_angle);
  std::cout<<"\n   === DUM 4 :: Search of exit from HELL ===\n\n";
  for (i = 0; i < imap_size[0]; i++)
    for (j = 0; j < imap_size[1]; j++)
      for (k = 0; k < imap_size[2]; k++)
	map1->setcell (i, j, k, map_random ());
  map1->setcell (ex_coord[0], ex_coord[1], ex_coord[2], 10);
  while (1)
    {
      image1 = map1->make_look ();
      std::
	cout << "health:" << health << ",armour:" << armour << ",bullets:" <<
	bullets;
      std::cout << "\n you see:\n";
      std::cout << "\n                 " << real_name (image1.f);
      std::cout << "\n " << real_name (image1.
				       l) << "                             "
	<< real_name (image1.r);
      if (image1.f > 0 && image1.f < 4)
	{
	  while (1)
	    {
	      emove = (int) (3.0 * rand () / (RAND_MAX + 1.0));
	      std::cout << "\n\n" << real_name (image1.
						f) <<
		" attacks you! Choose side to shoot: 4 - left, 5 - forward, 6 -right \?";
	      std::cin >> tty_in;
	      bullets--;
	      armour--;
	      if (armour < 0)
		armour = 0;
	      if (tty_in - 4 == emove)
		break;
	      health -= 10 - (int) (armour / 10);
	      if (health < 10 || bullets == -1)
		{
		  std::cout << "\n GAME OVER\n";
		  return 0;
		}
	    }
	  map1->make_clean_with_id (11);
	  continue;
	}
      std::cout << "\n 4 - left, 5 - forward, 6 -right \?";
      std::cin >> tty_in;
      switch (tty_in)
	{
	case 4:
	  map1->turn (0);
	  break;
	case 5:
	  if (image1.f != 0)
	    map1->movef ();
	  if (image1.f == 4)
	    map1->movez (1);
	  if (image1.f == 6)
	    map1->movez (-1);
	  if (image1.f == 7)
	    {
	      health += 25;
	      if (health > 100)
		health = 100;
	    }
	  if (image1.f == 8)
	    bullets += 4;
	  if (image1.f == 9)
	    armour += 1;
	  if (image1.f == 10)
	    {
	      std::cout << "\nCongratulations! You win!";
	      return 0;
	    }
	  break;
	case 6:
	  map1->turn (1);
	}
    }
  return 0;
}
