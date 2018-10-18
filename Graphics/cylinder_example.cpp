//
// Display a color cube
//
// Colors are assigned to each vertex and then the rasterizer interpolates
//   those colors across the triangles.  We us an orthographic projection
//   as the default projetion.

#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <iostream>

#include <GLUT/glut.h>

#include "Angel.h"
#include "simplemodels.h"


// Array of rotation angles (in degrees) for each coordinate axis
enum { Xaxis = 0, Yaxis = 1, Zaxis = 2, NumAxes = 3 };
int      Axis = Yaxis;
GLfloat  Theta1[NumAxes] = { 0.0, 0.0, 0.0 };
GLfloat  Theta2[NumAxes] = { 0.0, 0.0, 0.0 };
GLfloat  Theta3[NumAxes] = { 0.0, 0.0, 0.0 };

//----------------------------------------------------------------------------

size_t CUBE_OFFSET;
size_t COLOR_OFFSET;
size_t CYLINDER_OFFSET;
size_t SPHERE_OFFSET;
size_t TORUS_OFFSET;

GLuint program;
GLuint vPosition;
GLuint vNormal;
GLuint vColor;


void
init()
{
    // Load shaders and use the resulting shader program
    program = InitShader( "vshader21.glsl", "fshader21.glsl" );
    glUseProgram( program );
    
    //---------------------------------------------------------------------
    colorcube();
    colortube();
    colorbube();
    colortorus();
    //---------------------------------------------------------------------
    
    
    //----set offset variables
    
    CUBE_OFFSET = 0;
    COLOR_OFFSET = sizeof(points_cube);
    CYLINDER_OFFSET = COLOR_OFFSET + sizeof(colors);
    SPHERE_OFFSET = CYLINDER_OFFSET + sizeof(points_cylinder);
    TORUS_OFFSET = SPHERE_OFFSET + sizeof(points_sphere);
    
    // Create a vertex array object
    GLuint vao;
    glGenVertexArrays( 1, &vao );  // removed 'APPLE' suffix for 3.2
    glBindVertexArray( vao );
    
    // Create and initialize a buffer object
    GLuint buffer;
    glGenBuffers( 1, &buffer );
    glBindBuffer( GL_ARRAY_BUFFER, buffer );
    
    
     glBufferData( GL_ARRAY_BUFFER, sizeof(points_cube) + sizeof(colors) + sizeof(points_cylinder) + sizeof(points_sphere) + sizeof(points_torus), NULL, GL_STATIC_DRAW );
     glBufferSubData( GL_ARRAY_BUFFER, CUBE_OFFSET, sizeof(points_cube), points_cube );
     glBufferSubData( GL_ARRAY_BUFFER, COLOR_OFFSET, sizeof(colors), colors );
     glBufferSubData( GL_ARRAY_BUFFER, CYLINDER_OFFSET, sizeof(points_cylinder), points_cylinder );
     glBufferSubData( GL_ARRAY_BUFFER, SPHERE_OFFSET, sizeof(points_sphere), points_sphere );
     glBufferSubData( GL_ARRAY_BUFFER, TORUS_OFFSET, sizeof(points_torus), points_torus );
    
    //---------------------------------------------------------------------
    
    // set up vertex arrays
    vPosition = glGetAttribLocation( program, "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(CUBE_OFFSET) );
    
    vNormal = glGetAttribLocation( program, "vNormal" );
    glEnableVertexAttribArray( vNormal );
    
    vColor = glGetAttribLocation( program, "vColor" );
    glEnableVertexAttribArray( vColor );
    glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(COLOR_OFFSET) );
    //---------------------------------------------------------------------
    
    glEnable( GL_DEPTH_TEST );
    glClearColor( 1.0, 1.0, 1.0, 1.0 );
}



//----------------------------------------------------------------------------
vec4 eye = vec4(0.0, 0.0, -0.25, 1.0);
vec4 at = vec4(0.0, 0.0, 0.0, 1.0);
vec4 up = vec4(0.0, 1.0, 0.0, 0.0);
mat4 view_matrix;
mat4 proj_matrix;
bool spherical_camera = false;

float r = 0.5;
float td_y = 0.0, td_z = 0.0;

float sun_rot_angle = 0.0;
float sat_rot_angle = 0.0;
float sat_rev_angle = 0.0;
float ring_rot_angle = 0.0;

void
camera( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    
    //camera intrinsic parameters
    float left = -0.05;
    float right = 0.05;
    float bottom = -0.05;
    float top = 0.05;
    float zNear = 0.1;
    float zFar = 5000.0;
    
    proj_matrix = Frustum(left, right, bottom, top, zNear, zFar);
    
    glUniformMatrix4fv(glGetUniformLocation(program, "projection"), 1, GL_TRUE, proj_matrix);
    
    //camera extrinsic parameters
    if (spherical_camera == true)
    {
        float tr_y = td_y * M_PI/180.0;
        float tr_z = td_z * M_PI/180.0;
        eye.z = r * (cos(tr_z)) * cos(tr_y);
        eye.x = r * (cos(tr_z)) * sin(tr_y);
        eye.y = r * sin(tr_z);
        up = vec4(0.0, cos(tr_z), 0.0, 0.0);
        view_matrix = LookAt(eye, at, up);
        
        
        //vec4 n = normalize(eye - at);
        //vec4 u = vec4(normalize(cross(up,n)), 0.0);
        ////cout << u;
        //vec4 v = vec4(normalize(cross(n,u)), 0.0);
        //vec4 t = vec4(0.0, 0.0, 0.0, 2.0);
        //mat4 c = mat4(u, v , n, t);
        //view_matrix = c * Translate( -eye.x, -eye.y, -eye.z);
    }
    
    glUniformMatrix4fv(glGetUniformLocation(program, "view"), 1, GL_TRUE, view_matrix);
}

void
display( void )
{
    camera();
    
    //sun
    mat4  rot = RotateY( sun_rot_angle );
    mat4 transform = Translate( 0.0, 0.0, 0.0 ) * rot * Scale(1.5, 1.5, 1.5);
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glUniform1i( glGetUniformLocation(program, "obj_color_on"), true );
    glUniform4fv( glGetUniformLocation(program, "obj_color"), 1, vec4(0.99, 0.72, 0.07, 1.0) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    //saturn
    mat4 transform2 = RotateY( sat_rev_angle ) * Translate( 2.0, 0.0, 0.0 ) * RotateY( sat_rot_angle ) * Scale( 0.7, 0.7, 0.7 );
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform2 );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(SPHERE_OFFSET) );
    glUniform1i( glGetUniformLocation(program, "obj_color_on"), true );
    glUniform4fv( glGetUniformLocation(program, "obj_color"), 1, vec4(0.8, 0.8, 0.7, 1.0) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesSphere );
    
    
    //torus
    mat4 transform3 = RotateY( sat_rev_angle ) * Translate( 2.0, 0.0, 0.0 ) * RotateY( ring_rot_angle ) * RotateX( 90 )  * Scale( 1.0, 1.0, 0.05 );
    glUniformMatrix4fv( glGetUniformLocation( program, "model" ), 1, GL_TRUE, transform3 );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(TORUS_OFFSET) );
    glUniform1i( glGetUniformLocation(program, "obj_color_on"), true );
    glUniform4fv( glGetUniformLocation(program, "obj_color"), 1, vec4(0.6, 0.6, 0.6, 1.0) );
    glDrawArrays( GL_TRIANGLES, 0, NumVerticesTorus );
     
    glutSwapBuffers();
}

//----------------------------------------------------------------------------

void
keyboard( unsigned char key, int x, int y )
{
    if (!spherical_camera)
    {
        switch( key )
        {
            case 033: // Escape Key
                exit( EXIT_SUCCESS );
                break;
            case 'w': view_matrix *= Translate(0.0, 0.0, 0.1); break;
            case 'W': view_matrix *= Translate(0.0, 0.0, 0.5); break;
            case 's': view_matrix *= Translate(0.0, 0.0, -0.1); break;
            case 'S': view_matrix *= Translate(0.0, 0.0, -0.5); break;
            case 'a': view_matrix *= Translate(0.1, 0.0, 0.0); break;
            case 'A': view_matrix *= Translate(0.5, 0.0, 0.0); break;
            case 'd': view_matrix *= Translate(-0.1, 0.0, 0.0); break;
            case 'D': view_matrix *= Translate(-0.5, 0.0, 0.0); break;
            case 'j': view_matrix *= RotateY(-2.0); break;
            case 'l': view_matrix *= RotateY(2.0); break;
            case 'i': view_matrix *= RotateX(-2.0); break;
            case 'k': view_matrix *= RotateX(2.0); break;
            case 'c': spherical_camera = !spherical_camera; break;
            case 't': eye = vec4(0.0, 0.0, 0.5, 1.0);
                at = vec4(0.0, 0.0, 0.0, 1.0);
                up = vec4(0.0, 1.0, 0.0, 0.0);
                view_matrix = LookAt(eye, at, up); break;
        }
    }
    else
    {
        switch( key )
        {
            case 033: // Escape Key
                exit( EXIT_SUCCESS );
                break;
            case 'w': td_z += 5; break;
            case 's': td_z -= 5; break;
            case 'a': td_y -= 5; break;
            case 'd': td_y += 5; break;
            case 'c': spherical_camera = !spherical_camera; break;
            case 't': eye = vec4(0.0, 0.0, 0.5, 1.0);
                at = vec4(0.0, 0.0, 0.0, 1.0);
                up = vec4(0.0, 1.0, 0.0, 0.0);
                view_matrix = LookAt(eye, at, up); break;
                //td_y = 0.0; td_z = 0.0; break;
            case 'r': r += 0.5; break;
            case 'f': r -= 0.5;; break;
        }
    }
    
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
mouse( int button, int state, int x, int y )
{
    if ( state == GLUT_DOWN ) {
        switch( button ) {
            case GLUT_LEFT_BUTTON:    Axis = Xaxis;  break;
            case GLUT_MIDDLE_BUTTON:  Axis = Yaxis;  break;
            case GLUT_RIGHT_BUTTON:   Axis = Zaxis;  break;
        }
    }
}

//----------------------------------------------------------------------------

void
idle( void )
{
    Theta1[Axis] = fmod(Theta1[Axis]+0.0, 360.0);
    Theta2[Axis] = fmod(Theta2[Axis]+0.1, 360.0);
    Theta3[Axis] = fmod(Theta3[Axis]+0.5, 360.0);
    
    sun_rot_angle = fmod(sun_rot_angle + 0.05, 360.0);
    sat_rot_angle = fmod(sat_rot_angle + 0.05, 360.0);
    sat_rev_angle = fmod(sat_rev_angle + 0.25, 360.0);
    ring_rot_angle = fmod(ring_rot_angle + 0.1, 360.0);
    
    glutPostRedisplay();
}

//----------------------------------------------------------------------------

void
reshape( int w, int h )
{
    glViewport(0,0,w,h);
}

//----------------------------------------------------------------------------

int
main( int argc, char **argv )
{
    glutInit( &argc, argv );
    glutInitDisplayMode(GLUT_3_2_CORE_PROFILE | GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );
    glutInitWindowSize( 800, 800 );
    glutCreateWindow( "Color Cube" );
    
    init();
    
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutMouseFunc( mouse );
    glutIdleFunc( idle );
    
    glutMainLoop();
    return 0;
}