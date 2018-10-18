//----------------------------------------------------------------------------

const int NumVerticesCube = 36; //(6 faces)(2 triangles/face)(3 vertices/triangle)

extern vec4 points_cube[NumVerticesCube];
extern vec4 colors[NumVerticesCube];

void colorcube();


//----------------------------------------------------------------------------

const int segments = 16;
const int NumVerticesCylinder = segments*6 + segments*3*2;

extern vec4 points_cylinder[NumVerticesCylinder];

void colortube();


//----------------------------------------------------------------------------

const int ssegments = 32;
const int NumVerticesSphere = ssegments * 6 * ssegments; // + ssegments*3*2;

extern vec4 points_sphere[NumVerticesSphere];

void colorbube();


//----------------------------------------------------------------------------

const int tsegments = 32;
const int NumVerticesTorus = tsegments*6*tsegments;

extern vec4 points_torus[NumVerticesTorus];

void colortorus();