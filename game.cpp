#include "TXLib.h"


void shar_3D (int x, int y,
              int r,
              COLORREF cvet);


void draw_shar_3D (int *x, int *y,
                   int rmax,
                   int color1, int color2, int color3);


void game_ball_3D (int x1, int y1, int vx1, int vy1,
                   int x2, int y2, int vx2, int vy2,
                   int x3, int y3, int vx3, int vy3,
                   int x4, int y4, int vx4, int vy4,
                   double dt);



double dist1 (int x1, int y1,
              int x2, int y2);


void dist2 (int x1, int y1,
            int x2, int y2,
            int x3, int y3,
            int x4, int y4);

void move_game_ball (int *x, int *y, int *vx, int *vy,
                     double *dt);


void control_game_ball (int *vx, int *vy,
                        int up, int down, int left, int right, int space);



int main()
{
  txCreateWindow (1000, 600);


  game_ball_3D (4, 10, 5, 5,
                785, 10, 5, 5,
                795, 585, 5, 5,
                5, 585, 5, 5,
                1);


  //move_game_ball ();


  //control_game_ball ();


  /*draw_shar_3D (400, 300,
                  2,
                  0, 0);*/


  return 0;
}




void shar_3D (int x, int y,
              int r,
              COLORREF cvet)
{
  txSetColor (cvet);

  txSetFillColor (cvet);

  txCircle (x, y, r);
}




void draw_shar_3D (int *x, int *y,
                   int rmax,
                   int color1, int color2, int color3)
{
  int t = 0;


  while (t <= 50)
  {
    int tmp_rad = rmax - (rmax / 50.0) * t;
    COLORREF tmp_color = RGB (color1 + (color1 / 25.0) * t,
                              color3 + (color3 / 25.0) * t, color2 + (color2 / 25.0) * t );

    shar_3D (*x, *y, tmp_rad, tmp_color);

    t++;
  }
}




double dist1 (int x1, int y1, int x2, int y2)
{
  return sqrt ((x2  - x1) * (x2  - x1) + (y2 - y1) * (y2 - y1));
}




void game_ball_3D (int x1, int y1, int vx1, int vy1,
                   int x2, int y2, int vx2, int vy2,
                   int x3, int y3, int vx3, int vy3,
                   int x4, int y4, int vx4, int vy4,
                   double dt)
{
  while (true)
  {
    txSetColor (TX_BLACK);

    txSetFillColor (TX_BLACK);

    txClear ();

    double d1 = dist (x1, y1,
                      x3, y3);
    double d2 = dist (x1, y1,
                      x4, y4);


    double d3 = dist (x2, y2,
                      x3, y3);
    double d4 = dist (x2, y2,
                      x4, y4);


    double d5 = dist (x1, y1,
                      x2, y2);
    double d6 = dist (x2, y2,
                      x1, y1);


    if (d5 < 75 || d6 < 75)
    {
        (vx1 = - vx1);
        (vy1 = - vy1);


        (vx2 = - vx2);
        (vy2 = - vy2);
    }


    if (d1 < 150 || d2 < 150 || d3 < 150 || d4 < 150)
    {
      txMessageBox ("You Lose");

      break;
    }


    control_game_ball (&vx1, &vy1, VK_UP, VK_DOWN, VK_LEFT, VK_RIGHT, VK_SPACE);
    move_game_ball (&x1, &y1, &vx1, &vy1, &dt);


    draw_shar_3D (&x1, &y1,
                  50,
                  80, 0, 0);


    control_game_ball (&vx2, &vy2, 'W', 'S', 'A', 'D', VK_SPACE);
    move_game_ball (&x2, &y2, &vx2, &vy2, &dt);


    draw_shar_3D (&x2, &y2,
                  50,
                  0, 0, 80);


    move_game_ball (&x3, &y3, &vx3, &vy3, &dt);

    draw_shar_3D (&x3, &y3,
                  100,
                  0, 80, 0);


    move_game_ball (&x4, &y4, &vx4, &vy4, &dt);

    draw_shar_3D (&x4, &y4,
                  100,
                  80, 80, 0);


    txSleep (50);
  }
}




void move_game_ball (int *x, int *y, int *vx, int *vy,
                     double *dt)
{
  if ((*x) < 0)
    (*vx) = - (*vx);

  if ((*x) > 1000)
    (*vx) = - (*vx);

  if ((*y) < 0)
    (*vy) = - (*vy);

  if ((*y) > 600)
    (*vy) = - (*vy);


  *x = *x + *vx * *dt;

  *y = *y + *vy * *dt;

}




void control_game_ball (int *vx, int *vy,
                        int up, int down, int left, int right, int space)
{
  if (GetAsyncKeyState (up))
    (*vy)--;

  if (GetAsyncKeyState (down))
    (*vy)++;

  if (GetAsyncKeyState (left))
    (*vx)--;

  if (GetAsyncKeyState (right))
    (*vx)++;


  if (GetAsyncKeyState (space))
    (*vx) = 0;

  if (GetAsyncKeyState (space))
    (*vy) = 0;
}



