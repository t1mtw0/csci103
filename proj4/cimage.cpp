#include "cimage.h"
#include "bmplib.h"
#include "component.h"
#include <cmath>
#include <deque>
#include <iomanip>
#include <iostream>
// You shouldn't need other #include's - Ask permission before adding

CImage::CImage(const char *bmp_filename) {
    //  Note: readRGBBMP dynamically allocates a 3D array
    //    (i.e. array of pointers to pointers (1 per row/height) where each
    //    point to an array of pointers (1 per col/width) where each
    //    point to an array of 3 unsigned char (uint8_t) pixels [R,G,B values])

    // ================================================
    img_ = readRGBBMP(bmp_filename, h_, w_);
    // Leave this check
    if (img_ == NULL) {
        throw std::logic_error("Could not read input file");
    }

    // Set the background RGB color using the upper-left pixel
    for (int i = 0; i < 3; i++) {
        bgColor_[i] = img_[0][0][i];
    }

    // ======== This value should work - do not alter it =======
    // RGB "distance" threshold to continue a BFS from neighboring pixels
    bfsBgrdThresh_ = 60;

    // ================================================
    for (int i = 0; i < h_; ++i) {
        std::vector<int> v;
        for (int j = 0; j < w_; ++j) {
            v.push_back(-1);
        }
        labels_.push_back(v);
    }
    // ================================================
    // TO DO: Initialize any other data members
    components_ = {};
}

CImage::~CImage() { deallocateImage(img_); }

// Complete - Do not alter
bool CImage::isCloseToBground(uint8_t p1[3], double within) {
    // Computes "RGB" (3D Cartesian distance)
    double dist = std::sqrt(std::pow(p1[0] - bgColor_[0], 2) +
                            std::pow(p1[1] - bgColor_[1], 2) +
                            std::pow(p1[2] - bgColor_[2], 2));
    return dist <= within;
}

size_t CImage::findComponents() {
    size_t count = 0;
    for (int i = 0; i < h_; ++i) {
        for (int j = 0; j < w_; ++j) {
            if (!isCloseToBground(img_[i][j], bfsBgrdThresh_) &&
                labels_[i][j] == -1) {
                components_.push_back(bfsComponent(i, j, count++));
            }
        }
    }
    return count;
}

// Complete - Do not alter
void CImage::printComponents() const {
    std::cout << "Height and width of image: " << h_ << "," << w_ << std::endl;
    std::cout << std::setw(4) << "Ord" << std::setw(4) << "Lbl" << std::setw(6)
              << "ULRow" << std::setw(6) << "ULCol" << std::setw(4) << "Ht."
              << std::setw(4) << "Wi." << std::endl;
    for (size_t i = 0; i < components_.size(); i++) {
        const Component &c = components_[i];
        std::cout << std::setw(4) << i << std::setw(4) << c.label
                  << std::setw(6) << c.ulNew.row << std::setw(6) << c.ulNew.col
                  << std::setw(4) << c.height << std::setw(4) << c.width
                  << std::endl;
    }
}

int CImage::getComponentIndex(int mylabel) const {
    for (unsigned i = 0; i < components_.size(); ++i) {
        if (components_[i].label == mylabel)
            return i;
    }
    return -1;
}

void CImage::translate(int mylabel, int nr, int nc) {
    // Get the index of specified component
    int cid = getComponentIndex(mylabel);
    if (cid < 0) {
        return;
    }
    int h = components_[cid].height;
    int w = components_[cid].width;

    // ==========================================================
    // ADD CODE TO CHECK IF THE COMPONENT WILL STILL BE IN BOUNDS
    // IF NOT:  JUST RETURN.
    if (nr < 0 || nc < 0 || nr + h > h_ || nc + w > w_)
        return;
    // ==========================================================

    // If we reach here we assume the component will still be in bounds
    // so we update its location.
    Location nl(nr, nc);
    components_[cid].ulNew = nl;
}

void CImage::forward(int mylabel, int delta) {
    int cid = getComponentIndex(mylabel);
    if (cid < 0 || delta <= 0) {
        return;
    }
    unsigned int spot = cid + delta;
    if (spot >= components_.size())
        spot = components_.size() - 1;
    for (unsigned i = cid; i < spot; ++i) {
        Component temp = components_[i];
        components_[i] = components_[i + 1];
        components_[i + 1] = temp;
    }
}

void CImage::backward(int mylabel, int delta) {
    int cid = getComponentIndex(mylabel);
    if (cid < 0 || delta <= 0) {
        return;
    }
    int spot = cid - delta;
    if (spot < 0)
        spot = 0;
    for (int i = cid; i > spot; --i) {
        Component temp = components_[i];
        components_[i] = components_[i - 1];
        components_[i - 1] = temp;
    }
}

void CImage::save(const char *filename) {
    // Create another image filled in with the background color
    uint8_t ***out = newImage(bgColor_);

    for (unsigned i = 0; i < components_.size(); ++i) {
        Component com = components_[i];
        for (int r = 0; r < com.height; ++r) {
            for (int c = 0; c < com.width; ++c) {
                if (labels_[com.ulOrig.row + r][com.ulOrig.col + c] ==
                    com.label) {
                    for (int rgb = 0; rgb < 3; ++rgb) {
                        out[com.ulNew.row + r][com.ulNew.col + c][rgb] =
                            img_[com.ulOrig.row + r][com.ulOrig.col + c][rgb];
                    }
                }
            }
        }
    }

    writeRGBBMP(filename, out, h_, w_);
    // Add any other code you need after this
    deallocateImage(out);
}

// Complete - Do not alter - Creates a blank image with the background color
uint8_t ***CImage::newImage(uint8_t bground[3]) const {
    uint8_t ***img = new uint8_t **[h_];
    for (int r = 0; r < h_; r++) {
        img[r] = new uint8_t *[w_];
        for (int c = 0; c < w_; c++) {
            img[r][c] = new uint8_t[3];
            img[r][c][0] = bground[0];
            img[r][c][1] = bground[1];
            img[r][c][2] = bground[2];
        }
    }
    return img;
}

void CImage::deallocateImage(uint8_t ***img) const {
    for (int i = 0; i < h_; ++i) {
        for (int j = 0; j < w_; ++j) {
            delete[] img[i][j];
        }
        delete[] img[i];
    }
    delete[] img;
}

Component CImage::bfsComponent(int pr, int pc, int mylabel) {
    int neighbor_row[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
    int neighbor_col[8] = {0, -1, -1, -1, 0, 1, 1, 1};
    std::deque<Location> q;
    Location l(pr, pc);
    labels_[l.row][l.col] = mylabel;
    Component com(l, 1, 1, mylabel);
    q.push_back(l);
    while (!q.empty()) {
        Location l = q.front();
        q.pop_front();
        if (l.col < com.ulOrig.col) {
            com.ulOrig.col = l.col;
            com.ulNew.col = l.col;
            com.width++;
        }
        int nh = l.row - com.ulOrig.row + 1;
        int nw = l.col - com.ulOrig.col + 1;
        if (nh > com.height)
            com.height = nh;
        if (nw > com.width)
            com.width = nw;
        for (int i = 0; i < 8; ++i) {
            Location neighbor(l.row + neighbor_row[i], l.col + neighbor_col[i]);
            if (neighbor.row < 0 || neighbor.row >= h_ || neighbor.col < 0 ||
                neighbor.col >= w_)
                continue;
            if (labels_[neighbor.row][neighbor.col] == -1 &&
                !isCloseToBground(img_[neighbor.row][neighbor.col],
                                  bfsBgrdThresh_)) {
                labels_[neighbor.row][neighbor.col] = mylabel;
                q.push_back(neighbor);
            }
        }
    }
    return com;
}

// Complete - Debugging function to save a new image
void CImage::labelToRGB(const char *filename) {
    // multiple ways to do this -- this is one way
    std::vector<uint8_t[3]> colors(components_.size());
    for (unsigned int i = 0; i < components_.size(); i++) {
        colors[i][0] = rand() % 256;
        colors[i][1] = rand() % 256;
        colors[i][2] = rand() % 256;
    }

    for (int i = 0; i < h_; i++) {
        for (int j = 0; j < w_; j++) {
            int mylabel = labels_[i][j];
            if (mylabel >= 0) {
                img_[i][j][0] = colors[mylabel][0];
                img_[i][j][1] = colors[mylabel][1];
                img_[i][j][2] = colors[mylabel][2];
            } else {
                img_[i][j][0] = 0;
                img_[i][j][1] = 0;
                img_[i][j][2] = 0;
            }
        }
    }
    writeRGBBMP(filename, img_, h_, w_);
}

// Complete - Do not alter
const Component &CImage::getComponent(size_t i) const {
    if (i >= components_.size()) {
        throw std::out_of_range("Index to getComponent is out of range");
    }
    return components_[i];
}

// Complete - Do not alter
size_t CImage::numComponents() const { return components_.size(); }

// Complete - Do not alter
void CImage::drawBoundingBoxesAndSave(const char *filename) {
    for (size_t i = 0; i < components_.size(); i++) {
        Location ul = components_[i].ulOrig;
        int h = components_[i].height;
        int w = components_[i].width;
        for (int i = ul.row; i < ul.row + h; i++) {
            for (int k = 0; k < 3; k++) {
                img_[i][ul.col][k] = 255 - bgColor_[k];
                img_[i][ul.col + w - 1][k] = 255 - bgColor_[k];
            }
            // cout << "bb " << i << " " << ul.col << " and " << i << " " <<
            // ul.col+w-1 << endl;
        }
        for (int j = ul.col; j < ul.col + w; j++) {
            for (int k = 0; k < 3; k++) {
                img_[ul.row][j][k] = 255 - bgColor_[k];
                img_[ul.row + h - 1][j][k] = 255 - bgColor_[k];
            }
            // cout << "bb2 " << ul.row << " " << j << " and " << ul.row+h-1 <<
            // " " << j << endl;
        }
    }
    writeRGBBMP(filename, img_, h_, w_);
}

// Add other (helper) function definitions here
