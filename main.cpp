// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>

#include <iostream>

#include "VertexBuffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "RenderableData.h"
#include "Renderable.h"
#include "Renderer.h"
#include "Texture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Grid.h"
#include "Cube.h"
#include "Orientation.h"
#include "Cylinder.h"

#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "glm/gtc/quaternion.hpp"
#include "glm/gtx/quaternion.hpp"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BufferedAsyncSerial.h"
using namespace std;

GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() ) {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(960 * 2 , 540 * 2, "OpenGL-Test", NULL, NULL);
    if( window == NULL ) {
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}


vector<float> split(std::string phrase, std::string delimiter) {
    vector<float> list;
    std::string s = phrase;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        list.push_back(std::atof(token.c_str()));
        s.erase(0, pos + delimiter.length());
    }
    list.push_back(std::atof(s.c_str()));
    return list;
}

int main( void ) {
    GLFWwindow* window = InitWindow();
    if (!window)
        return -1;

    GLCall( glClearColor(1.0f, 1.0f, 1.0f, 1.0f) );
	GLCall( glEnable(GL_DEPTH_TEST) );
	GLCall( glDepthFunc(GL_LESS) );
    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {
        
        Grid grid;
    	float lengthAxis = 10000.0f;
    	float radiusAxis = 1.0f;
        Cylinder xAxis(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), lengthAxis, radiusAxis);
        Cylinder yAxis(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), lengthAxis, radiusAxis);
        Cylinder zAxis(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), lengthAxis, radiusAxis);

    	float lengthOrientation = 100.0f;
    	float radiusOrientation = 1.0f;
        Cylinder orientationX(vec3(1.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 0.0f, 0.0f), lengthOrientation, radiusOrientation);
        Cylinder orientationY(vec3(0.0f, 1.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f), lengthOrientation, radiusOrientation);
        Cylinder orientationZ(vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 1.0f), lengthOrientation, radiusOrientation);

        RenderableData gridData(grid);
        RenderableData xAxisData(xAxis);
        RenderableData yAxisData(yAxis);
        RenderableData zAxisData(zAxis);
        RenderableData xOrientationData(orientationX);
        RenderableData yOrientationData(orientationY);
        RenderableData zOrientationData(orientationZ);

    	float screenWidth = 960.0f;
    	float screenHeight = 540.0f;
    	float screenDepth = 10*2000.0f;

    	float halfScreenWidth = screenWidth/2;
    	float halfScreenHeight = screenHeight/2;
    	float halfScreenDepth = screenDepth/2;

    	mat4 Proj = glm::perspective(glm::radians(45.0f), (float) halfScreenWidth / (float)halfScreenHeight, 100.0f, 50000.0f);

        Shader shader("src/gl-renderer/res/shaders/Basic.shader");
        shader.Bind();

        double previousTime = glfwGetTime();
        int frameCount = 0;

        Renderer renderer;

    	mat4 View = mat4();

    	mat4 orientationModel = mat4(1.0f);
      	mat4 sceneModel = mat4(1.0f);

        mat4 MVPOrientation = mat4(1.0f);
        mat4 MVPScene = mat4(1.0f);

        vec3 position(0.0f, 0.0f, 0.0f);

        try {

            BufferedAsyncSerial serial("/dev/ttyACM0",4000000);
            std::string currentLine = "";
            quat currentOrientation = quat(1,0,0,0);

            do {
                std::string temp = serial.readStringUntil("\r\n");
                if (temp != "") {
                    currentLine = temp;
                }

                View = glm::lookAt(
                        position + vec3(130.f,100.f,350.f),
                        position,
                        glm::vec3(0.f,1.f,0.f)
                    );

                mat4 projectionView = Proj * View;

                if (currentLine.length() > 0) {
                    std::string delimiter = " ";

                    vector<float> quaternions = split(currentLine, delimiter);

                    currentOrientation = quat(quaternions[0], quaternions[1] ,quaternions[3], quaternions[2]);

                    mat4 rotation = mat4_cast(currentOrientation);
                    orientationModel =  rotation ;

                }

                MVPOrientation = projectionView * orientationModel;

                renderer.Clear();

                shader.SetUniformMat4f("u_MVP", MVPOrientation);
                renderer.Draw(xOrientationData, shader, GL_TRIANGLE_STRIP);
                renderer.Draw(yOrientationData, shader, GL_TRIANGLE_STRIP);
                renderer.Draw(zOrientationData, shader, GL_TRIANGLE_STRIP);

                MVPScene = projectionView * sceneModel;
                shader.SetUniformMat4f("u_MVP", MVPScene);
                renderer.Draw(xAxisData, shader, GL_TRIANGLE_STRIP);
                renderer.Draw(yAxisData, shader, GL_TRIANGLE_STRIP);
                renderer.Draw(zAxisData, shader, GL_TRIANGLE_STRIP);
                renderer.Draw(gridData , shader, GL_LINES);

                // Swap buffers
                glfwSwapBuffers(window);
                glfwPollEvents();

                double currentTime = glfwGetTime();
                frameCount++;

                if ( currentTime - previousTime >= 1.0 ) {
                    frameCount = 0;
                    previousTime = currentTime;
                }

            } // Check if the ESC key was pressed or the window was closed
            while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                    glfwWindowShouldClose(window) == 0 );

            serial.close();

        } catch(boost::system::system_error& e) {
            cout<<"Error: "<<e.what()<<endl;
            return 1;
        }



    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}