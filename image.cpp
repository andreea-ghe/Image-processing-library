#include "image.h"
#include "size.h"
#include "point.h"
#include <fstream>
using std::ostream;
using std::istream;

Image::Image(): m_data{nullptr}, m_width{0}, m_height{0} {};

Image::Image(unsigned int w, unsigned int h) {
    m_width = w;
    m_height = h;
    m_data = new unsigned char*[m_height];
    for (int i = 0; i < m_height; i ++)
        m_data[i] = new unsigned char[m_width];
    for (int i = 0; i < m_height; i ++)
        for (int j = 0; j < m_width; j ++)
            m_data[i][j] = 0;
}

unsigned int Image::width() const {
    return m_width;
}

unsigned int Image::height() const {
    return m_height;
}

Image::Image(const Image &other) {
    m_width = other.width();
    m_height = other.height();
    m_data = new unsigned char *[m_height];
    for (int i = 0; i < other.height(); i ++)
            m_data[i] = new unsigned char[m_width];
    for (int i = 0; i < other.height(); i ++)
        for (int j = 0; j < other.width(); j ++)
            m_data[i][j] = other.m_data[i][j];
}

Image &Image::operator=(const Image &other) {
    m_width = other.width();
    m_height = other.height();
    m_data = new unsigned char*[m_height];
    for (int i = 0; i < m_height; i ++)
        m_data[i] = new unsigned char[m_width];
    for (int i = 0; i < m_height; i ++)
        for (int j = 0; j < m_width; j ++)
            m_data[i][j] = other.m_data[i][j];
    return *this;
}

Size Image::size() const {
    return Size(m_width, m_height);
}

bool Image::isEmpty() const {
    return (m_width == 0 && m_height == 0 && m_data == nullptr);
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
    return m_data[x][y];
}

unsigned char& Image::at(Point pt) {
    return m_data[pt.get_x()][pt.get_y()];
}

unsigned char* Image::row(int y) {
    return m_data[y];
}

std::ostream& operator<<(std::ostream& os, const Image& dt) {
    os << "P2\n";
    os << dt.width() << ' ' << dt.height() << '\n';
    os << "255\n";
    for (int i = 0; i < dt.height(); i ++) {
        for (int j = 0; j < dt.width(); j ++)
            os << (int)dt.m_data[i][j] << ' ';
        os << '\n';
    }
    return os;
}

std::istream& operator>>(std::istream& is, Image& dt) {
    is >> dt.m_width >> dt.m_height;
    dt.m_data = new unsigned char*[dt.m_height];
    for (int i = 0; i < dt.height(); i ++) {
        dt.m_data[i] = new unsigned char[dt.m_width];
        for (int j = 0; j < dt.width(); j ++)
            is >> dt.m_data[i][j];
    }
    return is;
}

bool Image::load(std::string imagePath) {
    std::ifstream fin(imagePath);
    if (!fin.is_open())
        return false;

    std::string magic;
    int maxVal;
    fin >> magic >> m_width >> m_height >> maxVal;
    if (magic != "P2" || maxVal != 255)
        return false;
    m_data = new unsigned char*[m_height];
    for (int i = 0; i < m_height; i ++) {
        m_data[i] = new unsigned char [m_width];
        for (int j = 0; j < m_width; j ++) {
            int val;
            fin >> val;
            if (val < 0 || val > 255)
                return false;
            m_data[i][j] = val;
        }
    }
    fin.close();
    return true;
}

bool Image::save(std::string imagePath) const {

    std::ofstream fout(imagePath);
    if (!fout.is_open())
        return false;

    fout << "P2\n" << this->m_width << ' ' << this->m_height << '\n' << "255\n";
    for (int i = 0; i < this->m_height; i ++) {
        for (int j = 0; j < m_width; j ++)
            fout << static_cast<int>(this->m_data[i][j]) << ' ';
        fout << '\n';
    }
    fout.close();
    return true;
}

Image Image::zeros(unsigned int width, unsigned int height) {
    Image ans(width, height);
    for (int i = 0; i < height; i ++) {
        ans.m_data[i] = new unsigned char[width];
        for (int j = 0; j < width; j ++)
            ans.m_data[i][j] = 0;
    }
    return ans;
}

Image Image::ones(unsigned int width, unsigned int height) {
    Image ans(width, height);
    for (int i = 0; i < height; i ++) {
        ans.m_data[i] = new unsigned char[width];
        for (int j = 0; j < width; j ++)
            ans.m_data[i][j] = 1;
    }
    return ans;
}

Image Image::operator+(const Image &i) {
    if (m_width != i.width() || m_height != i.height()) {
        throw std::runtime_error("Images must have the same dimensions");
    }

    Image ans(m_width, m_height);
    ans.m_data = new unsigned char *[m_height];
    for (int h = 0; h < m_height; h ++){
        ans.m_data[h] = new unsigned char[m_width];
        for (int w = 0; w < m_width; w ++)
            ans.m_data[h][w] = m_data[h][w] + i.m_data[h][w];
    }
    return ans;
}

Image Image::operator-(const Image &i) {
    if (m_width != i.width() || m_height != i.height()) {
        throw std::runtime_error("Images must have the same dimensions");
    }

    Image ans(m_width, m_height);
    ans.m_data = new unsigned char *[m_height];
    for (int h = 0; h < m_height; h ++){
        ans.m_data[h] = new unsigned char[m_width];
        for (int w = 0; w < m_width; w ++)
            ans.m_data[h][w] = abs(m_data[h][w] - i.m_data[h][w]);
    }
    return ans;
}

Image Image::operator*(double s) {
    Image ans(m_width, m_height);
    ans.m_data = new unsigned char * [m_height];
    for (int h = 0; h < m_height; h ++){
        ans.m_data[h] = new unsigned char[m_width];
        for (int w = 0; w < m_width; w ++)
            ans.m_data[h][w] = m_data[h][w] * s;
    }
    return ans;
}

bool Image::getROI(Image &roiImg, Rectangle roiRect) {
    if(roiRect.get_p().get_x() + roiRect.get_s().get_width() > m_width || roiRect.get_p().get_y() + roiRect.get_s().get_height() > m_height || roiRect.get_p().get_x() >= m_width || roiRect.get_p().get_y() >= m_height)
        return false;

    roiImg.m_width = roiRect.get_s().get_width();
    roiImg.m_height = roiRect.get_s().get_height();
    roiImg.m_data = new unsigned char *[roiRect.get_s().get_height()];
    for (int i = 0; i < roiRect.get_s().get_height(); i ++) {
        roiImg.m_data[i] = new unsigned char [roiRect.get_s().get_width()];
        for (int j = 0; j < roiRect.get_s().get_width(); j ++)
            roiImg.m_data[i][j] = m_data[i + roiRect.get_p().get_y()][j + roiRect.get_p().get_x()];
    }
    return true;
}

bool Image::getROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
    if (x + width > m_width || y + height > m_height || x >= m_width || y >= m_height)
        return false;

    roiImg.m_width = width;
    roiImg.m_height = height;
    roiImg.m_data = new unsigned char * [height];
    for (unsigned int i = 0; i < height; i ++) {
        roiImg.m_data[i] = new unsigned char [width];
        for (unsigned int j = 0; j < width; j ++)
            roiImg.m_data[i][j] = m_data[i + y][j + x];
    }
    return true;
}

void Image::release() {
    for (int i = 0; i < m_height; i ++)
        delete[] m_data[i];
    delete[] m_data;
    m_data = nullptr;
    m_height = 0;
    m_width = 0;
}

Image::~Image() {
    release();
}
