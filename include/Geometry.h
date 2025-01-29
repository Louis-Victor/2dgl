#ifndef __GEOMETRY__
#define __GEOMETRY__
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include  <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>

#include "Shader.h"
#include "Window.h"

class Point{
    private:
        float x, y, z, r, g, b, a;
        float data[7];
    public:
        Point();
        Point(glm::vec2 pos);
        Point(glm::vec2 pos, float col);
        Point(glm::vec2 pos, glm::vec3 col);
        Point(glm::vec2 pos, glm::vec4 col);
        Point(glm::vec3 pos);
        Point(glm::vec3 pos, float col);
        Point(glm::vec3 pos, glm::vec3 col);
        Point(glm::vec3 pos, glm::vec4 col);

        Point& operator=(const Point& other);
        bool operator<(const Point& other);
        bool operator<=(const Point& other);
        bool operator>(const Point& other);
        bool operator>=(const Point& other);
        bool operator==(const Point& other);
        bool operator!=(const Point& other);
        Point operator+(Point& other);
        Point operator*(float scalar);
        Point operator-(const Point& other);
        Point operator/(float scalar);
        float getX();
        float getY();
        float getZ();
        float getR();
        float getG();
        float getB();
        float getA();
        glm::vec3 posVec();
        float* getData();
        void bind(unsigned int& VAO, unsigned int& VBO);
        void print();
};

class Line{
    private:
        Point p1, p2;
        float data[14];
    public:
        Line();
        Line(const Point& _p1, const Point& _p2);
        Line(const Line& line);
        Line& operator=(const Line& other);
        bool operator<(Line& other);
        bool operator<=(Line& other);
        bool operator>(Line& other);
        bool operator>=(Line& other);
        bool operator==(const Line& other);
        bool operator!=(const Line& other);
        float* getData();
        void bind(unsigned int& VAO, unsigned int& VBO);
        void draw(unsigned int& VAO, unsigned int& VBO,Shader& shader);
        Point getCenter();
        void print();
};

class LineVec{
    private:
        std::vector<Line> lines;
        bool isSorted(std::vector<Line> _lines);
        std::vector<Line> sort(std::vector<Line> _lines);
        float* data;
    public:
        LineVec();
        LineVec(const Line& line);
        LineVec(const Point& p1, const Point& p2);
        void add(const Line& line);
        void add(const Point& p1, const Point& p2);
        size_t size();
        Line get(int index);
        void set(int index, Line& line);
        Line pop(int index);
        bool isSorted();
        std::vector<Line> sort();
        void bind(unsigned int& VAO, unsigned int& VBO);
        void draw(unsigned int& VAO, unsigned int& VBO,Shader& shader);
        //std::vector<Point> getCenters();
        //std::string toString();
        void print();
};

// Simple graphis drawings SGD
namespace sgd{
    glm::vec4 _color;
    unsigned int _VAO, _VBO;
     const unsigned int shaderCount = 2;
    const char* shaderList[shaderCount] = {
        "main.vert",
        "main.frag"
    };
    Shader _shader(shaderList, shaderCount);
    Window window;

    void init();
    void setColor(float col);
    void setColor(float col, float a);
    void setColor(float r, float g, float b);
    void setColor(float r, float g, float b, float a);

    void  drawPoint(float x, float y);
    void  drawLine(float x1, float y1, float x2, float y2);
}




#endif
