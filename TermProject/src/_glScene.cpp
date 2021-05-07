#include "_glScene.h"
#include <_glLight.h>
#include <SOIL.h>

#include <math.h>
//#define YSCREEN 0.8
//#define XSCREEN 1.2

int ii=0;
_glScene::_glScene()
{
    //ctor
    level1 = true;
    level2 = level3 = false;
    doneInitializing = false;
    gameComplete = false;
}


_glScene::~_glScene()
{
    //dtor
}
GLint _glScene::initGL()
{
    glShadeModel(GL_SMOOTH);
    glClearColor(0.0f,0.0f,0.0f,0.0f);
    glClearDepth(1.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_COLOR_MATERIAL);
    _glLight myLight(GL_LIGHT0);
//--------------------------------------Game Level Control-------------------------------------------------------------------------
    if(level1)
    {
        for(int i=0;i<7;i++)
        {
          for(int j=0;j<7;j++)
          {
              scrnStng[i][j].level=1;
          }
        }
        background->parallaxInit("images/BG.png");
        timer->startTimer();
        myPly->playerInit(8,2,-1.5);
        myPly->plyImage->loadTexture("images/playerAnimated.png");
        enmy[0].enemyInit(10,1,3.8,2.15);//---------------------------------Enemy Initialization----
        enmy[0].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        enmy[1].enemyInit(10,1,-2.0,2.15);//---------------------------------Enemy Initialization----
        enmy[1].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        enmy[2].enemyInit(10,1,-3.0,1.15);//---------------------------------Enemy Initialization----
        enmy[2].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        doneInitializing = true;
    }
    if(level2)
    {
        for(int i=0;i<7;i++)
        {
          for(int j=0;j<7;j++)
          {
              scrnStng[i][j].level=2;
          }
        }
        background->parallaxInit("images/BG3.png");
        timer->startTimer();
        myPly->playerInit(8,2,-1.5);
        myPly->plyImage->loadTexture("images/playerAnimated.png");
        enmy[0].enemyInit(10,1,3.8,2.05);//---------------------------------Enemy Initialization----
        enmy[0].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        enmy[1].enemyInit(10,1,-3.8,2.15);//---------------------------------Enemy Initialization----
        enmy[1].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        enmy[2].enemyInit(10,1,-3.8,1.15);//---------------------------------Enemy Initialization----
        enmy[2].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        doneInitializing = true;
    }
    else if(level3)
    {
        for(int i=0;i<7;i++)
        {
          for(int j=0;j<7;j++)
          {
              scrnStng[i][j].level=3;
          }
        }
        msg->msgInit();
        msg->msgImage->loadTexture("images/unnamed.png");
        background->parallaxInit("images/BG4.png");
        timer->startTimer();
        myPly->playerInit(8,2,-1.125);
        myPly->plyImage->loadTexture("images/playerAnimated.png");
        enmy[0].enemyInit(10,1,3.8,1.95);//---------------------------------Enemy Initialization----
        enmy[0].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        enmy[1].enemyInit(10,1,-3.5,2.15);//---------------------------------Enemy Initialization----
        enmy[1].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        enmy[2].enemyInit(10,1,-3.5,1.15);//---------------------------------Enemy Initialization----
        enmy[2].enemyImage->loadTexture("images/zombie_walk.png");//---Enemy Image-------------
        doneInitializing = true;
    }
//-----------------------Screen Settings Initialization for Game.--------------------------------------
        h ="images/tile_";
        j =".png";
        for(int imgfile = 0; imgfile < 5; imgfile++)
        {
        str1<<imgfile;
        c = str1.str();
        k = h+c+j;
        t=&k[0];
          for(int y=0;y<4;y++)
          {
            scrnStng[imgfile][y].sceneInit(imgfile,y);
            scrnStng[imgfile][y].sceneImg->loadTexture(t);

          }
        str1.str("");
        str1.clear();
        }
//----------------------------Other Pages---------------------------------------
    landp->landingPageInit("images/landing.png");
    menup->menuPageInit("images/menu.png");
    helpp->helpPageInit("images/help.png");
    pup->popUpInit("images/pause.png");
    lpdecor->landingPageInit("images/rain.png");
    cp->creditsPageInit("images/credits.jpg");
    cpname->creditsPageInit("images/names.png");

    return true;
}

GLint _glScene::drawScene()
{

    if (kbMs->flag == 0)  //Landing page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear screen and depth buffer
        glLoadIdentity();
        glPushMatrix();
        glTranslated(0,0,-8.0);  //placing objects on screen
        glScalef(2.5, 2.5, 1.0);  //scale to fit within the screen

        landp -> renderBack(screenWidth, screenHeight);       //create background for landing page
        lpdecor -> renderBack(screenWidth, screenHeight);  //make rainfall on the landing page
        lpdecor -> scroll(true, "up", 0.0005);  //Rain scrolling on the landing page
        glPopMatrix();
    }

    if (kbMs->flag == 1)  //Menu page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear screen and depth buffer
        glLoadIdentity();
        glPushMatrix();
        glTranslated(0,0,-8.0);  //placing objects on screen
        glScalef(2.5, 2.4, 1.0);  //scale to fit within the screen
        menup -> renderBack(screenWidth, screenHeight);       //create background for game menu screen
        glPopMatrix();
    }

    if (kbMs->flag == 2)  //Help page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	//Clear screen and depth buffer
        glLoadIdentity();
        glPushMatrix();
        glTranslated(0,0,-8.0);  //placing objects on the screen
        glScalef(2.4, 2.4, 1.0);  //scale to fit within the screen
        helpp -> renderBack(screenWidth, screenHeight);       //create background for help page
        glPopMatrix();
    }

    if (kbMs->flag == 3)  //Game page
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(0.0f,0.2f,0.2f,0.3f);
        glLoadIdentity();

        glPushMatrix();
        glScalef(2.60, 2.45, 1.0);
        glBindTexture(GL_TEXTURE_2D,background->plxTexture->tex);
        background->renderBack(screenWidth,screenHeight);
        glPopMatrix();

        glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,myPly->plyImage->tex);
        myPly->drawPlayer();

        //------------------------------------Enemy Settings------------------------------------------------------
        glPushMatrix();

        for(int i=0;i<3;i++)
            {
                glBindTexture(GL_TEXTURE_2D,enmy[i].enemyImage->tex);
                enmy[i].drawEnemy();
            }
        glPopMatrix();

        //enemy and player actions
        if(timer->getTicks() > 120)
        {
            myPly->actions();
            for(int i=0;i<3;i++)
            {
                enmy[i].actions();
            }
            timer->resetTime();
        }
        glPopMatrix();

//------------------------------------Screen Settings Draw + Collision------------------------------------
        glPushMatrix(); // group my object

        myPly->colCount=0;
         for(int imgfile = 0; imgfile < 7; imgfile++)
        {

          for(int y=0;y<7;y++)
          {
            glBindTexture(GL_TEXTURE_2D, scrnStng[imgfile][y].sceneImg->tex);
            scrnStng[imgfile][y].drwScn(imgfile,y);

            clsn = colsn->isBoundedCollision(*myPly,&scrnStng[imgfile][y],imgfile,y);

            //check if player collides with the top of the tile
            //if yes then hold the position
            //else change the action trigger to fall down
            if(clsn == true)
            {
                //PLAYER COLLIDES WITH THE TOP OF THE TILE
                if(scrnStng[imgfile][y].colUp)
                {
                    myPly->plyPosY = (scrnStng[imgfile][y].scenePos[imgfile][y].y + (scrnStng[imgfile][y].sceneScale[imgfile].y/2.0)) + (myPly->playerScale.y/2.0) - 0.1;
                }

                //PLAYER COLLIDES WITH THE LEFT OF THE TILE
                if(scrnStng[imgfile][y].colLeft)
                {
                    if(kbMs->rightKey)
                    {
                        myPly->playerPos.x = (scrnStng[imgfile][y].scenePos[imgfile][y].x - (scrnStng[imgfile][y].sceneScale[imgfile].x/2.0)) - (myPly->playerScale.x/2.0) - 0.1;
                    }
                }

                //PLAYER COLLIDES WITH THE RIGHT OF THE TILE
                if(scrnStng[imgfile][y].colRight)
                {
                    if(kbMs->leftKey)
                    {
                        myPly->playerPos.x = (scrnStng[imgfile][y].scenePos[imgfile][y].x + (scrnStng[imgfile][y].sceneScale[imgfile].x/2.0)) + (myPly->playerScale.x/2.0) - 0.1;
                        //myPly->playerPos.x -= 0.02;
                    }
                }

                //PLAYER COLLIDES WITH THE BOTTOM OF THE TILE
                if(scrnStng[imgfile][y].colBottom)
                {
                    if(kbMs->upKey)
                    {
                        myPly->playerPos.y = (scrnStng[imgfile][y].scenePos[imgfile][y].y - (scrnStng[imgfile][y].sceneScale[imgfile].y/2.0)) - (myPly->playerScale.y/2.0);
                    }
                }
            }
            else
            {
                myPly->colCount++;
                if(myPly->colCount==49 && myPly->actionTrigger != myPly->JUMP && myPly->actionTrigger != myPly->WALK_LEFT_JUMP && myPly->actionTrigger != myPly->WALK_RIGHT_JUMP)
                {
                    myPly->actionTrigger = myPly->FALL_DOWN;
                }
                scrnStng[imgfile][y].colLeft= false;
                scrnStng[imgfile][y].colRight= false;
                scrnStng[imgfile][y].colUp= false;
                scrnStng[imgfile][y].colBottom= false;
                //scrnStng[imgfile][y].colPlyTrue=false;
                //myPly->actionTrigger = myPly->FALL_DOWN;
            }



            //for each enemy, check the collision with the top of the tile
            //if yes, then auto scroll
            //if not, then fall down

            for(int i=0;i<3;i++)
            {
                //if enm collision with tile top
                //then autoscroll()
                //else falldown
                enmy[i].colEnmTrue = colsn->isBoundedCollision2(enmy[i],&scrnStng[imgfile][y],imgfile,y);
                if(enmy[i].colEnmTrue)
                {
                    enmy[i].autoScroll();
                    enmy[i].colCount=0;
                }
                else
                {
                    enmy[i].colCount++;
                    //cout<<colEnmCount<<endl;
                    if(enmy[i].colCount==49)
                    {
                        enmy[i].autoScrollCol();
                        enmy[i].colCount=0;
                    }
                }

            }

            if(enmClsn == true)
            {

                //cout<<"Collision of enemy = true at"<<imgfile+1<<" "<<y+1<<endl;
            }
          }

        }
        glPopMatrix(); // exit the group

        if(myPly->playerPos.x > 4.2)
        {
            if(level1)
            {
                level1 = !level1;
                level2 = !level2;
            }
            else if(level2)
            {
                level2 = !level2;
                level3 = !level3;
            }
            else if(level3)
            {
                level1 = !level1;
                level3 = !level3;
            }
            doneInitializing = false;
        }


    }

    if (kbMs->flag == 4)  //pause game pop-up page
    {
        //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen and Depth buffer
        //glLoadIdentity();
        glPushMatrix();
        //glTranslated(0.0, 0.0, -7.0);  //placing objects on the screen
        glScalef(1.0, 1.0, 1.0);  //pause screen pop-up scaling
        pup -> renderBack(screenWidth, screenHeight);       //create background for pause pop-up screen
        glPopMatrix();
    }

    if (kbMs->flag == 5)  //credits page
    {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();
    glPushMatrix();
    glTranslated(0,0,-8.0);     //placing objects
    glScalef(2.5, 2.5, 1.0);  //scaling to fit on the screen
    cp -> renderBack(screenWidth, screenHeight);       //create background for credits page

    glScalef(1/1.1, 1/1.1, 1.0);  //de-scaling for credits name
    cpname -> renderBack(screenWidth, screenHeight);  //create background for names
    cpname -> cpscroll(true, "down", 0.0005);  //scrolling the names
    glPopMatrix();
    }

}


void _glScene::resizeGLScene(int width, int height)
{
    screenWidth= width;
    screenHeight=height;

    float aspectRatio = (float)width/(float)height;
    glViewport(0,0,width,height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluPerspective(45.0,aspectRatio,0.1,100);
    //glOrtho(-3.0,3.0,-1.5,1.5,0.1,100);
    glOrtho(-width/350.0,width/350.0,-height/350.0,height/350.0,0.1,100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


int _glScene::winMsg(HWND	hWnd,			// Handle For This Window
                     UINT	uMsg,			// Message For This Window
					 WPARAM	wParam,			// Additional Message Information
					 LPARAM	lParam)
{   kbMs->wParam = wParam;

    switch (uMsg)									// Check For Windows Messages
	{

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{

		    //to move background
		    kbMs->moveEnv(background, 0.005);
            kbMs->moveEnv(background1, 0.015);

            //kbMs->keys[wParam] = true;
		    kbMs->keyPressed(myPly);
		    kbMs->keyPressed(landp);       //Handling key inputs on the landing page
            kbMs->keyPressed(menup);       //Handling key inputs on the menu page
            kbMs->keyPressed(helpp);       //Handling key inputs on the help page
            kbMs->keyPressed(pup);      //Handling key inputs on the game pause pop up screen
            kbMs->keyPressed(cp);       //handling key inputs on credits page
			break;
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
		    kbMs->keyUp();
		    kbMs->keyUp(myPly);
			break;								// Jump Back
		}

		case WM_LBUTTONDOWN:
            {
//                kbMs ->mouseDown(modelTeapot, LOWORD(lParam),HIWORD(lParam));
                kbMs ->mouseDown(landp);

                break;
            }
        case WM_RBUTTONDOWN:
            {
//                kbMs ->mouseDown(modelTeapot, LOWORD(lParam),HIWORD(lParam));
                kbMs ->mouseDown(landp);
              break;
            }
        case WM_MBUTTONDOWN:
            {
                break;
            }
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            {
                kbMs->mouseUp();
               break;
            }
        case WM_MOUSEMOVE:
            {
//                kbMs ->mouseMove(modelTeapot, LOWORD(lParam),HIWORD(lParam));
               break;
            }

        case WM_MOUSEWHEEL:
            {
//                kbMs->mouseWheel(modelTeapot,(float)GET_WHEEL_DELTA_WPARAM(wParam));
                break;
            }
	}
}
