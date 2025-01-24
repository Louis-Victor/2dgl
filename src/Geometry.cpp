#include <GL/glew.h>
 #include <GLFW/glfw3.h>
#include  <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <vector>
#include <iostream>
#include <algorithm>

#include "Geometry.h"
#include "Shader.h"
#include  "glHelper.h"

// POINT
Point::Point():
    Point::Point(glm::vec2(0.0f,0.0f))
{
    //std::cout << "Point()\n";
    //std::cout << "\t\n";
}
Point::Point(glm::vec2 pos):
    Point::Point(glm::vec3(pos,0.0f))
{
    //std::cout << "Point(glm::vec2 pos)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ")\n";
}
Point::Point(glm::vec2 pos, float col):
    Point::Point(glm::vec3(pos,0.0f),col)
{
    //std::cout << "Point(glm::vec2 pos, float col)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ")\n";
    //std::cout << "\t(" << col << ")\n";
}
Point::Point(glm::vec2 pos, glm::vec3 col):
    Point::Point(glm::vec3(pos,0.0f),col)
{
    //std::cout << "Point(glm::vec2 pos, glm::vec3 col)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ")\n";
    //std::cout << "\t(" << col.x << ", " << col.y << ", " <<  col.z << ")\n";
}
Point::Point(glm::vec2 pos, glm::vec4 col):
    Point::Point(glm::vec3(pos,0.0f),col)
{
    //std::cout << "Point(glm::vec2 pos, glm::vec4 col)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ")\n";
    //std::cout << "\t(" << col.x << ", " << col.y << ", " <<  col.z << ", " << col.w << ")\n";
}
Point::Point(glm::vec3 pos):
    Point::Point(pos,1.0f)
{
    //std::cout << "Point(glm::vec3 pos)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
}
Point::Point(glm::vec3 pos, float col):
    Point::Point(pos,glm::vec3(col,col,col))
{
    //std::cout << "Point(glm::vec3 pos, float col)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    //std::cout << "\t(" << col << ")\n";
}
Point::Point(glm::vec3 pos, glm::vec3 col):
    Point::Point(pos,glm::vec4(col,1.0f))
{
    //std::cout << "Point(glm::vec3 pos, glm::vec3 col)\n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    //std::cout << "\t(" << col.x << ", " << col.y << ", " <<  col.z << ")\n";
}
Point::Point(glm::vec3 pos, glm::vec4 col) :
    x(pos.x),y(pos.y),z(pos.z),r(col.x),g(col.y),b(col.z),a(col.w)
{
    //std::cout << "Point(glm::vec3 pos, glm::vec4 col) \n";
    //std::cout << "\t(" << pos.x << ", " << pos.y << ", " << pos.z << ")\n";
    //std::cout << "\t(" << col.x << ", " << col.y << ", " <<  col.z << ", " << col.w << ")\n";
}

Point& Point::operator=(const Point& other){
    if((*this) != other){
        x = other.x;
        y = other.y;
        z = other.z;
        r = other.r;
        g = other.g;
        b = other.b;
        a = other.a;
    }
    
    return *this;
}
bool Point::operator<(const Point& other){
    if(x < other.x) return true;
    if(x > other.x) return false;
    if(y < other.y) return true;
    return false;
}
bool Point::operator<=(const Point& other){
    if(x <= other.x) return true;
    if(x > other.x) return false;
    if(y <= other.y) return true;
    return false;
}
bool Point::operator>(const Point& other){
    if(x > other.x) return true;
    if(x < other.x) return false;
    if(y > other.y) return true;
    return false;
}
bool Point::operator>=(const Point& other){
    if(x >= other.x) return true;
    if(x < other.x) return false;
    if(y >= other.y) return true;
    return false;
}

Point Point::operator+(Point& other){
    glm::vec3 pos = glm::vec3(x+other.x,y+other.y,z+other.z);
    glm::vec4 col = glm::vec4((r+other.r)/2.0f,(g+other.g)/2.0f,(b+other.b)/2.0f,(a+other.a)/2.0f);
    Point p(pos, col);

    return p;
}
Point Point::operator-(const Point& other){
    return Point(
            glm::vec3(x-other.x,y-other.y,z-other.z),
            glm::vec3((r+other.r)/2.0f,(g+other.g)/2.0f,(b+other.b)/2.0f));
}
Point Point::operator*(float scalar){
    return Point(
            glm::vec3(x*scalar,y*scalar,z*scalar),
            glm::vec4(r,g,b,a));
}
Point Point::operator/(float scalar){
    return (*this)*(1/scalar);
}

bool Point::operator==(const Point& other){
    return x == other.x && y == other.y && z == other.z && r == other.r && g == other.g && b == other.b && a == other.a;
}

bool Point::operator!=(const Point& other){
    return !(*this == other);
}

float Point::getX(){
    return x;
}
float Point::getY(){
    return y;
}
float Point::getZ(){
    return z;
}
float Point::getR(){
    return r;
}
float Point::getG(){
    return g;
}
float Point::getB(){
    return b;
}
float Point::getA(){
    return a;
}
glm::vec3 Point::posVec(){
    return glm::vec3(x,y,z);
}
float* Point::getData(){
    data[0] = x;
    data[1] = y;
    data[2] = z;
    data[3] = r;
    data[4] = g;
    data[5] = b;
    data[6] = a;

    return data;
}
void Point::bind(unsigned int& VAO, unsigned int& VBO){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    getData();

    glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glEnableVertexAttribArray(0);
}

void Point::print(){
    std::cout << this << "\n";
    std::cout << x << " ";
    std::cout << y << " ";
    std::cout << z << "\n";
    std::cout << "(" << x << ", " << y << ", " << z << ")\n";
    std::cout << "\tR: "<< r << " G: " << g << " B: " << b << " A: " << a << "\n";
}

// LINE
Line::Line() : Line::Line(*(new Point()),*(new Point())) {}
Line::Line(const Line& line): Line::Line(line.p1,line.p2){}
Line::Line(const Point& _p1, const Point& _p2) : p1(_p1), p2(_p2){}
Line& Line::operator=(const Line& other){
    if(this != &other){
        p1 = other.p1;
        p2 = other.p2;
    }

    return *this;
}

bool Line::operator<(Line& other){
    Point c1 = getCenter();
    Point c2 = other.getCenter();
    return c1 < c2;//getCenter() < other.getCenter();
}
bool Line::operator>(Line& other){
    return getCenter() > other.getCenter();
}
bool Line::operator<=(Line& other){
    return getCenter() <= other.getCenter();
}
bool Line::operator>=(Line& other){
    return getCenter() >= other.getCenter();
}

bool Line::operator==(const Line& other){
    return p1 == other.p1 && p2 == other.p2;
}
bool Line::operator!=(const Line& other){
    return !(*this == other);
}
float* Line::getData(){
    data[0] = p1.getX();
    data[1] = p1.getY();
    data[2] = p1.getZ();
    data[3] = p1.getR();
    data[4] = p1.getG();
    data[5] = p1.getB();
    data[6] = p1.getA();

    data[7] = p2.getX();
    data[8] = p2.getY();
    data[9] = p2.getZ();
    data[10] = p2.getR();
    data[11] = p2.getG();
    data[12] = p2.getB();
    data[13] = p2.getA();

    return data;
}
void Line::bind(unsigned int& VAO, unsigned int& VBO){
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);

    getData();

    glBufferData(GL_ARRAY_BUFFER,sizeof(data),data,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,7*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glEnableVertexAttribArray(0);
}

void Line::draw(unsigned int& VAO, unsigned int& VBO, Shader& shader){

    bind(VAO,VBO);
    shader.use();
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO); // ?
    glLineWidth(5.0f);
    glDrawArrays(GL_LINES,0,2);
    glBindVertexArray(0);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        std::cerr << "OpenGL error: " << err << "\n";
    }
}

Point Line::getCenter(){
    return Point(((p1+p2)/2.0f).posVec());
}

void Line::print(){
    std::cout << "p1\n\t";
    p1.print();
    std::cout << "p2\n\t";
    p2.print();
}

// LineVec
LineVec::LineVec(){}
LineVec::LineVec(const Line& line){
    add(line);
}
LineVec::LineVec(const Point& p1, const Point& p2){
    add(p1,p2);
}
void LineVec::add(const Line& line){
    lines.push_back(Line(line));
}
void LineVec::add(const Point& p1, const Point& p2){
    lines.push_back(Line(p1,p2));
}
size_t LineVec::size(){
    return lines.size();
}

Line LineVec::get(int index){
    return lines[index];
}
void LineVec::set(int index, Line& line){
    lines[index] = line;
}
Line LineVec::pop(int index){
    Line returnLine = lines[index];
    lines.erase(lines.begin()+index);
    return returnLine;
}
bool LineVec::isSorted(std::vector<Line> _lines){
    if(_lines.size() <= 1) return true;
    for(size_t i=0;i<_lines.size()-1;i++){
        if(_lines[i] > _lines[i+1]) return false;
    }
    return true;
}
bool  LineVec::isSorted(){
    return isSorted(lines);
}
std::vector<Line> LineVec::sort(std::vector<Line> _lines){
    if(isSorted(_lines))  return _lines;
    int sz = _lines.size()/2;
    std::vector<Line>::const_iterator first = _lines.begin();
    std::vector<Line>::const_iterator mid = _lines.begin()+sz;
    std::vector<Line>::const_iterator end = _lines.end();
    std::vector<Line> lVec(first,mid);
    std::vector<Line> rVec(mid,end);

    std::cout << "-------LVEC-------\n";
    for(size_t i=0;i<lVec.size();i++){
        lVec[i].print();
    }
    std::cout << "-------RVEC-------\n";
    for(size_t i=0;i<rVec.size();i++){
        rVec[i].print();
    }

    lVec = sort(lVec);
    rVec = sort(rVec);


    size_t i=0;
    size_t j=0;
    std::vector<Line> newVec;
    while(i<lVec.size() && j<rVec.size()){
        if(lVec[i] < rVec[j]){
            newVec.push_back(lVec[i]);
            i++;
        }else{
            newVec.push_back(lVec[j]);
            j++;
        }
    }
    for(size_t ii=i;ii<lVec.size();ii++){
        newVec.push_back(lVec[ii]);
    }
    for(size_t jj=j;jj<rVec.size();jj++){
        newVec.push_back(rVec[jj]);
    }
    std::cout << "-------NEWVEC-------\n";
    for(size_t i=0;i<rVec.size();i++){
        newVec[i].print();
    }
    

    return newVec;

}
std::vector<Line> LineVec::sort(){
    if(isSorted()) return lines;
    else return sort(lines);
}
void LineVec::draw(unsigned int& VAO, unsigned int& VBO, Shader& shader){
    for(size_t i=0;i<size();i++){
        lines[i].draw(VAO,VBO,shader);
    }
}
void LineVec::print(){
    for(size_t i=0;i<size();i++){
        std::cout << "------ Line " << i << " -------\n";
        lines[i].print();
    }
}
