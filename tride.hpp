/*
 * TrideLib v0.0.5
 * 3D Engine library 
 * 
 * Copyright (C) 2005-2010 Kurashov Artem Konstantinovich
 *
 *  TrideLib is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  TrideLib is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 */

struct eyesviewlfr
{
  int l, f, r;
};

class map_engine
{
public:
  map_engine (int, int, int, int, int, int, int);
   ~map_engine ();
  int getindex (int, int, int);
  int getcell (int, int, int);
  void setcell (int, int, int, int);
  void turn (int);
  void movef ();
  void movez (int);
  eyesviewlfr make_look ();
  void make_clean_with_id (int);
  int get_hero_coordz (int);
private:
  void mk_set ();
  int *map_data, map_width, map_length, map_height, hero_coordz[3];
  int angle_of_hero;
  int mk[2];
};

map_engine::map_engine (int smap_width, int smap_length, int smap_height,
			int start_x, int start_y, int start_z,
			int start_angle)
{
  map_width = smap_width;
  map_length = smap_length;
  map_height = smap_height;
  map_data = new int[smap_width * smap_length * smap_height];
  angle_of_hero = start_angle;
  hero_coordz[0] = start_x;
  hero_coordz[1] = start_y;
  hero_coordz[2] = start_z;
}

map_engine::~map_engine ()
{
  delete[]map_data;
}

int
map_engine::getindex (int mx, int my, int mz)
{
  return map_width * map_length * mz + map_width * my + mx;
}

int
map_engine::getcell (int mcx, int mcy, int mcz)
{
  return map_data[getindex (mcx, mcy, mcz)];
}

void
map_engine::setcell (int msx, int msy, int msz, int msv)
{
  map_data[getindex (msx, msy, msz)] = msv;
}

void
map_engine::turn (int side_code)
{
  if (side_code == 0)
    angle_of_hero++;
  else
    angle_of_hero--;
  if (angle_of_hero < 0)
    angle_of_hero = 3;
  if (angle_of_hero > 3)
    angle_of_hero = 0;
}

void
map_engine::mk_set ()
{
  switch (angle_of_hero)
    {
    case 0:
      mk[0] = 0;
      mk[1] = 1;
      break;
    case 1:
      mk[0] = -1;
      mk[1] = 0;
      break;
    case 2:
      mk[0] = 0;
      mk[1] = -1;
      break;
    case 3:
      mk[0] = 1;
      mk[1] = 0;
    }
}

void
map_engine::movef ()
{
  mk_set ();
  hero_coordz[0] += mk[0];
  hero_coordz[1] += mk[1];
  if (hero_coordz[0] < 1)
    hero_coordz[0] = 1;
  if (hero_coordz[0] > map_width - 1)
    hero_coordz[0] = map_width - 1;
  if (hero_coordz[1] < 1)
    hero_coordz[1] = 1;
  if (hero_coordz[1] > map_length - 1)
    hero_coordz[1] = map_length - 1;
}

void
map_engine::movez (int step_z)
{
  hero_coordz[2] += step_z;
  if (hero_coordz[2] > map_height - 1)
    hero_coordz[2] = map_height - 1;
  if (hero_coordz[2] < 0)
    hero_coordz[2] = 0;
}

eyesviewlfr map_engine::make_look ()
{
  eyesviewlfr
    eview;
  int
    ml_xyz[3];
  ml_xyz[0] = hero_coordz[0];
  ml_xyz[1] = hero_coordz[1];
  ml_xyz[2] = hero_coordz[2];
  mk_set ();
  ml_xyz[0] += mk[0];
  ml_xyz[1] += mk[1];
  eview.f = getcell (ml_xyz[0], ml_xyz[1], ml_xyz[2]);
  turn (1);
  mk_set ();
  ml_xyz[0] = hero_coordz[0];
  ml_xyz[1] = hero_coordz[1];
  ml_xyz[2] = hero_coordz[2];
  ml_xyz[0] += mk[0];
  ml_xyz[1] += mk[1];
  eview.r = getcell (ml_xyz[0], ml_xyz[1], ml_xyz[2]);
  turn (0);
  turn (0);
  mk_set ();
  ml_xyz[0] = hero_coordz[0];
  ml_xyz[1] = hero_coordz[1];
  ml_xyz[2] = hero_coordz[2];
  ml_xyz[0] += mk[0];
  ml_xyz[1] += mk[1];
  eview.l = getcell (ml_xyz[0], ml_xyz[1], ml_xyz[2]);
  turn (1);
  return eview;
}

void
map_engine::make_clean_with_id (int obj_id)
{
  int ml_xyz[3];
  ml_xyz[0] = hero_coordz[0];
  ml_xyz[1] = hero_coordz[1];
  ml_xyz[2] = hero_coordz[2];
  mk_set ();
  ml_xyz[0] += mk[0];
  ml_xyz[1] += mk[1];
  setcell (ml_xyz[0], ml_xyz[1], ml_xyz[2], obj_id);
}

int
map_engine::get_hero_coordz (int cid)
{
  return hero_coordz[cid];
}
