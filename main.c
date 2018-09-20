#include <curses.h>
#include <windows.h>
#define addsym(a,b,c) mvwaddch(panels[xx][yy],a,b,c);Sleep(50);wrefresh(panels[xx][yy]);
#define drawbox(a) wattron(panels[xx][yy],COLOR_PAIR(a));box(panels[xx][yy], 0, 0);wrefresh(panels[xx][yy]);wattroff(panels[xx][yy],COLOR_PAIR(a));


int main() {
  //INIT OPTIONS
  initscr();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  //INIT VARIABLES
  int start_y, start_x, key, x, y, turn, won, chkturn,cunt;
  int xo[3][3] = {{0,0,0},{0,0,0}};
  won=cunt=0;

  start_x = getmaxx(stdscr) / 2 - 9;
  start_y = 3;
  turn=chkturn= 1;

  //INIT BOXES
  WINDOW *panels[3][3]={{0,0,0},{0,0,0}};
  WINDOW *checkbox;
  refresh();


  //PRINT INSTRUCTIONS
  mvwprintw(stdscr,getmaxy(stdscr)-1,20,"To Move Use ");
  attron(A_REVERSE);
  wprintw(stdscr,"Arrows") ;
  attroff(A_REVERSE);
  wprintw(stdscr,"\tTo Turn in press ");
  attron(A_REVERSE);
  wprintw(stdscr,"Enter");
  attroff(A_REVERSE);
  wrefresh(stdscr);

  //INIT MAIN COORDS
  int xx, yy;
  yy=xx=0;
  x = start_x;
  y = start_y;

  //INIT COLORS
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_GREEN);
  init_pair(2, COLOR_WHITE, COLOR_WHITE);

  //DRAW BOXES

  for(int z = 0;TRUE;){
    panels[xx][yy] = newwin(7,7,y,x);
    drawbox(2);
    ++z;
    if(z == 9){break;}
    if (xx == 2){xx=0; x = start_x; ++yy; y+=6;}
    else{++xx; x+=6;}
  }

  //DRAW CHECKBOX
  checkbox = newwin(7,7,getmaxy(stdscr)/2-3,60);
  mvprintw(getmaxy(stdscr)/2-5,60,"CURRENT");
  mvprintw(getmaxy(stdscr)/2-4,59,"CHARACTER");
  wattron(checkbox,COLOR_PAIR(2));
  box(checkbox, 0, 0);


  mvwaddch(checkbox,2,2,'X');
  mvwaddch(checkbox,2,4,'X');
  mvwaddch(checkbox,3,3,'X');
  mvwaddch(checkbox,4,2,'X');
  mvwaddch(checkbox,4,4,'X');

  wattroff(checkbox,COLOR_PAIR(2));
  wrefresh(checkbox);
  xx=yy=0;



  //MAIN LOOP

  for(int count=0;TRUE;){
    //CHECK FOR WIN
    do{
     if(xo[0][0]==chkturn && xo[1][1]==chkturn && xo[2][2]==chkturn){won=chkturn;break;}
     if(xo[0][0]==chkturn && xo[0][1]==chkturn &&xo[0][2]==chkturn){won=chkturn;break;}
     if(xo[0][0]==chkturn && xo[1][0]==chkturn && xo[2][0]==chkturn){won=chkturn;break;}

     if(xo[2][0]==chkturn && xo[1][1]==chkturn && xo[0][2]==chkturn){won=chkturn;break;}
     if(xo[2][0]==chkturn && xo[2][1]==chkturn && xo[2][2]==chkturn){won=chkturn;break;}

     if(xo[2][2]==chkturn && xo[1][2]==chkturn && xo[0][2]==chkturn){won=chkturn;break;}
     if(xo[2][1]==chkturn && xo[1][1]==chkturn && xo[0][1]==chkturn){won=chkturn;break;}
     if(xo[1][0]==chkturn && xo[1][1]==chkturn && xo[1][2]==chkturn){won=chkturn;break;}

     if(cunt>=9)won=3;

   } while(FALSE);
     //IF WIN
     if(won!=0){
      //DRAW WIN MESSAGE
      
      if(won == 3){mvprintw(getmaxy(stdscr)/2,10,"DRAW!");}
      if(won == 1){mvprintw(getmaxy(stdscr)/2,10,"X WINS!");}
      if(won == 2){mvprintw(getmaxy(stdscr)/2,10,"O WINS!");}

      xx=yy=0;
      //REDRAW FIELD
      for(int z = 0;TRUE;){

        werase(panels[xx][yy]);
        drawbox(2);
        wrefresh(panels[xx][yy]);
        xo[xx][yy]=0;
        ++z;
        if(z == 9){break;}
        if (xx == 2){xx=0; ++yy;}
        else{++xx; }
    }
    won=0;
    turn=chkturn=1;
    cunt=0;
    xx=yy=0;
    continue;
  }

    chkturn = turn;
    //HIGHLIGHT SELECTED BOX
    drawbox(1);

    //GET KEY
    key = getch();

    //RESTORE PREVIOUS BOX COLOR
    drawbox(2);

    //KEY INPUT CHECK
    switch (key) {
      //LEFT
      case KEY_LEFT:if(xx != 0){--xx;continue;}else{continue;}

      //RIGHT
      case KEY_RIGHT:if(xx != 2){++xx;continue;}else{continue;}

      //UP
      case KEY_UP:if(yy != 0){--yy;continue;}else{continue;}

      //DOWN
      case KEY_DOWN:if(yy != 2){++yy;continue;}else{continue;}

      //TURN IN
      case 10:

        //SET CHAMBER TO ACTUAL CHARACTER
        if(xo[xx][yy]==0){xo[xx][yy]=turn;cunt+=1;}

        wattron(panels[xx][yy],COLOR_PAIR(2));
        wattron(checkbox,COLOR_PAIR(2));

        //PRINT CURRENT CHARACTER
        switch (xo[xx][yy]) {
          //IF X
          case 1: {
            //PRINT X
            addsym(2,2,'X'); //THIS PRINTS
            addsym(2,4,'X');
            addsym(3,3,'X'); //X X
            addsym(4,2,'X'); // X
            addsym(4,4,'X'); //X X

            werase(checkbox);
            box(checkbox, 0, 0);
            mvwaddch(checkbox,2,2,'O');
            mvwaddch(checkbox,2,3,'O');
            mvwaddch(checkbox,2,4,'O');
            mvwaddch(checkbox,3,2,'O');
            mvwaddch(checkbox,3,4,'O');
            mvwaddch(checkbox,4,2,'O');
            mvwaddch(checkbox,4,3,'O');
            mvwaddch(checkbox,4,4,'O');

            turn=2;

            wrefresh(checkbox);

            continue;
        }

          //IF O
          case 2: {
            //PRINT O
            addsym(2,2,'O');
            addsym(2,3,'O');//THIS PRINTS
            addsym(2,4,'O');
            addsym(3,2,'O');//OOO
            addsym(3,4,'O');//O O
            addsym(4,2,'O');//OOO
            addsym(4,3,'O');
            addsym(4,4,'O');

            werase(checkbox);
            box(checkbox, 0, 0);
            mvwaddch(checkbox,2,2,'X');
            mvwaddch(checkbox,2,4,'X');
            mvwaddch(checkbox,3,3,'X');
            mvwaddch(checkbox,4,2,'X');
            mvwaddch(checkbox,4,4,'X');

            turn=1;
            wrefresh(panels[xx][yy]);
            wrefresh(checkbox);

            continue;
        }

        wattroff(panels[xx][yy],COLOR_PAIR(2));
        wattroff(checkbox,COLOR_PAIR(2));

        continue;
      }
    }

  }
  getch();
  endwin();
  return 0;
}
