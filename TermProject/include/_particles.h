#ifndef _PARTICLES_H
#define _PARTICLES_H

#include<math.h>
<<<<<<< Updated upstream
=======
#include <GL/gl.h>
>>>>>>> Stashed changes

#define MAX_DROPS 50000
#define GRAVITY -0.001


class _particles
{
    public:
        _particles();
        virtual ~_particles();
<<<<<<< Updated upstream
=======
        int numDrops;
>>>>>>> Stashed changes

        typedef struct{
                bool alive;
                float posX;
                float posY;
                float posZ;

                float xDir;
                float yDir;

                float mass;

        }pts;

        pts drops[MAX_DROPS];

        void drawDrops();
        void update();
        void particleGenerator();

    protected:

    private:
};

#endif // _PARTICLES_H