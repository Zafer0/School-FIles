#include "Angel.h"
#include "simplemodels.h"




//----------------------------------------------------------------------------
vec4 points_cube[NumVerticesCube];
vec4 colors[NumVerticesCube];

// Vertices of a unit cube centered at origin, sides aligned with axes
vec4 vertices[8] = {
    vec4( -0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5,  0.5,  0.5, 1.0 ),
    vec4(  0.5, -0.5,  0.5, 1.0 ),
    vec4( -0.5, -0.5, -0.5, 1.0 ),
    vec4( -0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5,  0.5, -0.5, 1.0 ),
    vec4(  0.5, -0.5, -0.5, 1.0 )
};

// RGBA colors
vec4 vertex_colors[8] = {
    vec4( 0.1, 0.1, 0.1, 1.0 ),  // black
    vec4( 1.0, 0.0, 0.0, 1.0 ),  // red
    vec4( 1.0, 1.0, 0.0, 1.0 ),  // yellow
    vec4( 0.0, 1.0, 0.0, 1.0 ),  // green
    vec4( 0.0, 0.0, 1.0, 1.0 ),  // blue
    vec4( 1.0, 0.0, 1.0, 1.0 ),  // magenta
    vec4( 0.9, 0.9, 0.9, 1.0 ),  // white
    vec4( 0.0, 1.0, 1.0, 1.0 )   // cyan
};



//----------------------------------------------------------------------------

// quad generates two triangles for each face and assigns colors
//    to the vertices
int Index = 0;
void
quad( int a, int b, int c, int d )
{
    colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[b]; Index++;
    colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[a]; Index++;
    colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[c]; Index++;
    colors[Index] = vertex_colors[a]; points_cube[Index] = vertices[d]; Index++;
}

//----------------------------------------------------------------------------

// generate 12 triangles: 36 vertices and 36 colors
void
colorcube()
{
    quad( 1, 0, 3, 2 );
    quad( 2, 3, 7, 6 );
    quad( 3, 0, 4, 7 );
    quad( 6, 5, 1, 2 );
    quad( 4, 5, 6, 7 );
    quad( 5, 4, 0, 1 );
}






//---- cylinder model
//----------------------------------------------------------------------------
vec4 points_cylinder[NumVerticesCylinder];
vec4 vertices_cylinder[4];

// quad generates two triangles for each face and assigns colors to the vertices
void
quad_cylinder( int a, int b, int c, int d )
{
    points_cylinder[Index] = vertices_cylinder[a];
    Index++;
    points_cylinder[Index] = vertices_cylinder[b];
    Index++;
    points_cylinder[Index] = vertices_cylinder[c];
    Index++;
    points_cylinder[Index] = vertices_cylinder[a];
    Index++;
    points_cylinder[Index] = vertices_cylinder[c];
    Index++;
    points_cylinder[Index] = vertices_cylinder[d];
    Index++;
}


float const bottom = -0.5;
float const top    = 0.5;

void
colortube(void)
{
    float r = 0.5;
    Index = 0;
    
    for ( int n = 0; n < segments; n++ )
    {
        GLfloat const t0 = 2 * M_PI * (float)n / (float)segments;
        GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)segments;
        
        points_cylinder[Index].x = 0.0;
        points_cylinder[Index].y = top;
        points_cylinder[Index].z = 0.0;
        points_cylinder[Index].w = 1.0;
        Index++;
        points_cylinder[Index].x = cos(t0) * r;
        points_cylinder[Index].y = top;
        points_cylinder[Index].z = sin(t0) * r;
        points_cylinder[Index].w = 1.0;
        Index++;
        points_cylinder[Index].x = cos(t1) * r;
        points_cylinder[Index].y = top;
        points_cylinder[Index].z = sin(t1) * r;
        points_cylinder[Index].w = 1.0;
        Index++;
    }
    
    
    int num;
    for ( int n = 0; n < segments; n++ )
    {
        num = 0;
        float x = 0.0, y = 0.0, r = 0.5;
        
        GLfloat const t0 = 2 * M_PI * (float)n / (float)segments;
        GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)segments;
        
        //quad vertex 0
        vertices_cylinder[num].x = cos(t0) * r;
        vertices_cylinder[num].y = bottom;
        vertices_cylinder[num].z = sin(t0) * r;
        vertices_cylinder[num++].w = 1.0;
        //quad vertex 1
        vertices_cylinder[num].x = cos(t1) * r;
        vertices_cylinder[num].y = bottom;
        vertices_cylinder[num].z = sin(t1) * r;
        vertices_cylinder[num++].w = 1.0;
        //quad vertex 2
        vertices_cylinder[num].x = cos(t1) * r;
        vertices_cylinder[num].y = top;
        vertices_cylinder[num].z = sin(t1) * r;
        vertices_cylinder[num++].w = 1.0;
        //quad vertex 3
        vertices_cylinder[num].x = cos(t0) * r;
        vertices_cylinder[num].y = top;
        vertices_cylinder[num].z = sin(t0) * r;
        vertices_cylinder[num++].w = 1.0;
        
        quad_cylinder( 0, 1, 2, 3 );
    }
    
    
    for ( int n = 0; n < segments; n++ )
    {
        GLfloat const t0 = 2 * M_PI * (float)n / (float)segments;
        GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)segments;
        
        points_cylinder[Index].x = 0.0;
        points_cylinder[Index].y = bottom;
        points_cylinder[Index].z = 0.0;
        points_cylinder[Index].w = 1.0;
        Index++;
        points_cylinder[Index].x = cos(t1) * r;
        points_cylinder[Index].y = bottom;
        points_cylinder[Index].z = sin(t1) * r;
        points_cylinder[Index].w = 1.0;
        Index++;
        points_cylinder[Index].x = cos(t0) * r;
        points_cylinder[Index].y = bottom;
        points_cylinder[Index].z = sin(t0) * r;
        points_cylinder[Index].w = 1.0;
        Index++;
    }
    
}





//---- sphere model
//----------------------------------------------------------------------------
vec4 points_sphere[NumVerticesSphere];
vec4 vertices_sphere[4];

// quad generates two triangles for each face and assigns colors to the vertices
void
quad_sphere( int a, int b, int c, int d )
{
    points_sphere[Index] = vertices_sphere[a];
    Index++;
    points_sphere[Index] = vertices_sphere[b];
    Index++;
    points_sphere[Index] = vertices_sphere[c];
    Index++;
    points_sphere[Index] = vertices_sphere[a];
    Index++;
    points_sphere[Index] = vertices_sphere[c];
    Index++;
    points_sphere[Index] = vertices_sphere[d];
    Index++;
}


void
colorbube(void)
{
    float r = 0.5;
    Index = 0;
    float ph_top = M_PI/(float)ssegments;
    float ph_bottom = M_PI-ph_top;
    
    for( int m = 0; m < ssegments; m++ )
    {
        float p0 = m * M_PI/(float)ssegments;
        float p1 = (m+1) * M_PI/(float)ssegments;
        
        int num;
        for ( int n = 0; n < ssegments; n++ )
        {
            num = 0;
            float r = 0.5;
            
            GLfloat const t0 = 2 * M_PI * (float)n / (float)ssegments;
            GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)ssegments;
            
            //quad vertex 0
            vertices_sphere[num].x = r*sin(p1)*cos(t0);
            vertices_sphere[num].y = r*cos(p1);
            vertices_sphere[num].z = r*sin(p1)*sin(t0);
            vertices_sphere[num++].w = 1.0;
            //quad vertex 1
            vertices_sphere[num].x = r*sin(p1)*cos(t1);
            vertices_sphere[num].y = r*cos(p1);
            vertices_sphere[num].z = r*sin(p1)*sin(t1);
            vertices_sphere[num++].w = 1.0;
            //quad vertex 2
            vertices_sphere[num].x = r*sin(p0)*cos(t1);
            vertices_sphere[num].y = r*cos(p0);
            vertices_sphere[num].z = r*sin(p0)*sin(t1);
            vertices_sphere[num++].w = 1.0;
            //quad vertex 3
            vertices_sphere[num].x = r*sin(p0)*cos(t0);
            vertices_sphere[num].y = r*cos(p0);
            vertices_sphere[num].z = r*sin(p0)*sin(t0);
            vertices_sphere[num++].w = 1.0;
            
            quad_sphere( 0, 1, 2, 3 );
        }
    }
}


//---- torus model
//----------------------------------------------------------------------------
vec4 points_torus[NumVerticesTorus];
vec4 vertices_torus[4];

// quad generates two triangles for each face and assigns colors to the vertices
void
quad_torus( int a, int b, int c, int d )
{
    points_torus[Index] = vertices_torus[a];
    Index++;
    points_torus[Index] = vertices_torus[b];
    Index++;
    points_torus[Index] = vertices_torus[c];
    Index++;
    points_torus[Index] = vertices_torus[a];
    Index++;
    points_torus[Index] = vertices_torus[c];
    Index++;
    points_torus[Index] = vertices_torus[d];
    Index++;
}


void
colortorus(void)
{
    float r = 0.15;
    float rd = 0.6;
    Index = 0;
    float x,y;
    
    for( int m = 0; m < tsegments; m++ )
    {
        GLfloat const p0 = 2 * M_PI * (float)m / (float)tsegments;
        GLfloat const p1 = 2 * M_PI * (float)(m+1) / (float)tsegments;
        
        int num;
        for ( int n = 0; n < tsegments; n++ )
        {
            num = 0;
            float x = 0.0, y = 0.0;
            
            GLfloat const t0 = 2 * M_PI * (float)n / (float)tsegments;
            GLfloat const t1 = 2 * M_PI * (float)(n+1) / (float)tsegments;
            
            //quad vertex 0
            x = cos(t0) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t0) * r;
            // rotated by p1
            vertices_torus[num].x = x*cos(p1) - y*sin(p1);
            vertices_torus[num].y = x*sin(p1) + y*cos(p1);
            vertices_torus[num++].w = 1.0;
            
            //quad vertex 1
            x = cos(t1) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t1) * r;
            // rotated by p1
            vertices_torus[num].x = x*cos(p1) - y*sin(p1);
            vertices_torus[num].y = x*sin(p1) + y*cos(p1);
            vertices_torus[num++].w = 1.0;
            
            //quad vertex 2
            x = cos(t1) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t1) * r;
            // rotated by p0
            vertices_torus[num].x = x*cos(p0) - y*sin(p0);
            vertices_torus[num].y = x*sin(p0) + y*cos(p0);
            
            vertices_torus[num++].w = 1.0;
            
            //quad vertex 3
            x = cos(t0) * r + rd;
            y = 0.0;
            vertices_torus[num].z = sin(t0) * r;
            // rotated by p0
            vertices_torus[num].x = x*cos(p0) - y*sin(p0);
            vertices_torus[num].y = x*sin(p0) + y*cos(p0);
            
            vertices_torus[num++].w = 1.0;
            
            quad_torus( 0, 1, 2, 3 );
        }
    }
    
    
}