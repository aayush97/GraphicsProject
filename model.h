#ifndef MODEL_H
#define MODEL_H

#include "vectormath.h"
#include "face.h"
#include <vector>

class Model
{
    public:

        bool loadModel(const char *);

        std::vector<Vector> v;
        std::vector<Vector> vn;
        //vector<Vector> vt;
        std::vector<Face> f;


};

#endif // MODEL_H
