#include<iostream>
#include<GL/glut.h>
#include<vector>
#include<math.h>
using namespace std;

int width=700,height=600,f;
vector<pair<float,float> > points;

class Line
{
public:
    int dx,dy;
    float xinc,yinc,x,y;

    void draw_pixel(int x,int y)
    {
         glColor3f(1.0,0.0,0.0);
         glBegin(GL_POINTS);
                 glVertex2i(x,y);
                 glEnd();
                glFlush();

    }

    void DDA()
    {
        for(unsigned int i=0;i<points.size()-1;i++)
        {  int steps;
             x=points[i].first;
            y=points[i].second;

            dx = points[i+1].first - points[i].first;
            dy = points[i+1].second - points[i].second;

            steps= abs(dx)>abs(dy) ? abs(dx) : abs(dy) ;
            cout<<steps;
            xinc= dx/(float)steps;
            yinc= dy/(float)steps;

           // cout<<xinc<<endl;
          //  cout<<yinc<<endl;

            glColor3f(1.0,0.0,0.0);
            for(int j=0;j<=steps;j++)
            {
                draw_pixel( round(x), round(y));
                x=x+xinc;
                y=y+yinc;
            }
        }
    }

    void Bresenham()
    {

      for(unsigned int i=0;i<points.size()-1;i++)
      {
        int dp,xend,yend,x1,x2,y1,y2;

        x1=points[i].first;
        y1=points[i].second;
        x2=points[i+1].first;
        y2=points[i+1].second;

     	 dy = ( y2 -  y1);
	     dx = ( x2 -  x1);
	    int m =  dy* dx;

     	if(abs( dy) < abs( dx))
        {
		if( x1 >  x2)
		{
			x = x2;
			y = y2;
			xend = x1;
			xend = x1;
		}
		else{
			x = x1;
			y = y1;
			xend = x2;
		}
		 dy = abs( dy);
		 dx = abs( dx);
		 dp = (2 *  dy) -  dx;
		draw_pixel( x, y);
		while(x < xend){
			++x;
			if(dp < 0)
				dp = dp + (2*dy);
			else{
				y = (m>=0)?(y+1):(y-1);
				dp += 2*(dy - dx);
			}
			 draw_pixel( x, y);
		}
	}
	else{
		 dy = abs( dy);
		 dx = abs( dx);
		 dp = (2 *  dx) -  dy;
		if( y1 >  y2){
			x = x2;
			y = y2;
			yend = y1;
		}
		else{
			x = x1;
			y = y1;
			yend = y2;
		}
		 draw_pixel( x, y);
		while(y < yend){
			++y;
			if(dp < 0)
				dp += (2*dx);
			else{
				x = (m>=0)?(x+1):(x-1);
				dp += 2*(dx - dy);
			}
			 draw_pixel( x, y);
		}
        }
      }

    }

};
Line l;

void my_display()
{


}

void menu(int p)
{
  switch(p)
    {
    case 1:
       if(f>1)
        l.DDA();
        break;
    case 2:
        if(f>1)
        l.Bresenham();
        break;
    case 3:
        glClearColor(0.0,0.0,0.0,0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
      break;
    }
    points.clear();
  // glutDetachMenu(GLUT_RIGHT_BUTTON);
  f=0;
}

void my_mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN )
        {   f++;
            pair<float,float> p;
            p.first=(float)(x);
            p.second=(float)((height-y));
            points.push_back(p);
          // cout<<p.first<<endl;
           //cout<<p.second<<endl;

        }
     if(button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN  && points.size()>=2 )
        {
        glutCreateMenu(menu);
        glutAddMenuEntry("DDA",1);
        glutAddMenuEntry("Bresenham",2);
        glutAddMenuEntry("Clear",3);
        glutAttachMenu(GLUT_RIGHT_BUTTON);

        }

}
void myinit()
{
    glClearColor(0.0,0.0,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,width,0,height);
    glFlush();

}

int main(int argc,char* argv[])
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(5,5);
    glutInitWindowSize(width,height);
    glutCreateWindow("Drawing");

    glutDisplayFunc(my_display);
    glutMouseFunc(my_mouse);
    myinit();
    glutMainLoop();

    return 0;
}
