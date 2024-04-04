// #include <opencv2/opencv.hpp>
// #include <iostream>
// #include <vector>

// using namespace cv;
// using namespace std;

// void displayPixelValues(const Mat &block)
// {
//     cout << "Pixel values of the block:" << endl;
//     for (int i = 0; i < block.rows; ++i)
//     {
//         for (int j = 0; j < block.cols; ++j)
//         {
//             cout << static_cast<int>(block.at<uchar>(i, j)) << " ";
//         }
//         cout << endl;
//     }
//     cout << endl;
// }

// void rotateBlock(const Mat &src, Mat &dst, double angle)
// {
//     Point2f center(src.cols / 2.0, src.rows / 2.0);
//     Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
//     warpAffine(src, dst, rotationMatrix, src.size());
// }

// // Figure out
// void flipBlock(const Mat &src, Mat &dst, int flipCode)
// {
//     flip(src, dst, flipCode);
// }

// double calculateAbsoluteDifference(const Mat &block1, const Mat &block2)
// {
//     // Initialize the absolute difference
//     double absDiff = 0.0;

//     // Iterate over each pixel and compute absolute differences
//     for (int i = 0; i < block1.rows; ++i)
//     {
//         for (int j = 0; j < block1.cols; ++j)
//         {
//             absDiff += abs(static_cast<double>(block1.at<uchar>(i, j)) - static_cast<double>(block2.at<uchar>(i, j)));
//         }
//     }

//     return absDiff;
// }

// int main()
// {
//     // Read the input image
//     Mat originalImage = imread("./monkey.png");
//     // Resize the image to 64x64
//     Mat resizedImage;
//     resize(originalImage, originalImage, Size(64, 64));
//     resize(originalImage, resizedImage, Size(32,32));

//     // Define the size of the domain blocks
//     const int block_size = 4;

//     // Vector to store the coordinates and transformations of the closest range block for each domain block
//     vector<vector<vector<int>>> closest_blocks(originalImage.rows - block_size + 1, vector<vector<int>>(originalImage.cols - block_size + 1, vector<int>(4, -1)));

//     // Loop over all possible domain blocks
//     for (int i = 0; i <= originalImage.rows - block_size; ++i)
//     {
//         for (int j = 0; j <= originalImage.cols - block_size; ++j)
//         {
//             // Extract current domain block from the original image
//             Mat domain_block = originalImage(Rect(j, i, block_size, block_size));

//             // Initialize variables to track the minimum absolute difference and the coordinates of the closest range block
//             double min_abs_diff = numeric_limits<double>::max();
//             int closest_x = -1;
//             int closest_y = -1;
//             int closest_rotation = -1;
//             int closest_flipcode = -1;

//             // Loop over all possible range blocks in the resized image
//             for (int r = 0; r <= resizedImage.rows - block_size; ++r)
//             {
//                 for (int c = 0; c <= resizedImage.cols - block_size; ++c)
//                 {
//                     // Extract current range block from the resized image
//                     Mat range_block = resizedImage(Rect(c, r, block_size, block_size));

//                     // Loop over all possible rotations (0, 90, 180, 270 degrees)
//                     for (int rotation = 0; rotation < 360; rotation += 90) {
//                         // Loop over all possible flip codes (0, 1, -1)
//                         for (int flipcode = -2; flipcode <= 1; ++flipcode) {
//                             // Create a copy of the range block
//                             Mat transformed_block = range_block.clone();

//                             // Rotate the range block
//                             rotateBlock(transformed_block, transformed_block, rotation);

//                             // Flip the range block
//                             if(flipcode != -2) flipBlock(transformed_block, transformed_block, flipcode);

//                             // Calculate the absolute difference between the domain block and the transformed range block
//                             double abs_diff = calculateAbsoluteDifference(domain_block, transformed_block);

//                             // Update the minimum absolute difference and the coordinates of the closest range block
//                             if (abs_diff < min_abs_diff) {
//                                 min_abs_diff = abs_diff;
//                                 closest_x = c;
//                                 closest_y = r;
//                                 closest_rotation = rotation;
//                                 closest_flipcode = flipcode;
//                             }
//                         }
//                     }
//                 }
//             }

//             // Store the coordinates and transformations of the closest range block for the current domain block
//             // cout<<"Calculated (" << i << "," << j << ")"<<endl;
//             closest_blocks[i][j][0] = closest_x;
//             closest_blocks[i][j][1] = closest_y;
//             closest_blocks[i][j][2] = closest_rotation;
//             closest_blocks[i][j][3] = closest_flipcode;
//         }
//     }

//     // For debugging
//     // cout<< closest_blocks[0][0][0] << " " << closest_blocks[0][0][1] << " " << closest_blocks[0][0][2] << " " << closest_blocks[0][0][3];

//     // Output the coordinates and transformations of the closest range block for each domain block
//     for (int i = 0; i < closest_blocks.size(); ++i)
//     {
//         for (int j = 0; j < closest_blocks[0].size(); ++j)
//         {
//             cout << "[" << closest_blocks[i][j][0] << "," << closest_blocks[i][j][1] << "," << closest_blocks[i][j][2] << "," << closest_blocks[i][j][3] << "] ";
//         }
//         cout << endl;
//     }

//     return 0;
// }

#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

void displayPixelValues(const Mat &block)
{
    cout << "Pixel values of the block:" << endl;
    for (int i = 0; i < block.rows; ++i)
    {
        for (int j = 0; j < block.cols; ++j)
        {
            cout << static_cast<int>(block.at<uchar>(i, j)) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void rotateBlock(const Mat &src, Mat &dst, double angle)
{
    Point2f center(src.cols / 2.0, src.rows / 2.0);
    Mat rotationMatrix = getRotationMatrix2D(center, angle, 1.0);
    warpAffine(src, dst, rotationMatrix, src.size());
}

// Figure out
void flipBlock(const Mat &src, Mat &dst, int flipCode)
{
    flip(src, dst, flipCode);
}

double calculateAbsoluteDifference(const Mat &block1, const Mat &block2)
{
    // Initialize the absolute difference
    double absDiff = 0.0;

    // Iterate over each pixel and compute absolute differences
    for (int i = 0; i < block1.rows; ++i)
    {
        for (int j = 0; j < block1.cols; ++j)
        {
            absDiff += abs(static_cast<double>(block1.at<uchar>(i, j)) - static_cast<double>(block2.at<uchar>(i, j)));
        }
    }

    return absDiff;
}

int main()
{
    // Read the input image
    Mat originalImage = imread("./monkey.png");
    // Resize the image to 64x64
    Mat resizedImage;
    resize(originalImage, originalImage, Size(64, 64));
    resize(originalImage, resizedImage, Size(32,32));

    // Define the size of the domain blocks
    const int block_size = 4;

    // Vector to store the coordinates and transformations of the closest range block for each domain block
    vector<vector<vector<int>>> closest_blocks(originalImage.rows / block_size, vector<vector<int>>(originalImage.cols / block_size, vector<int>(4, -1)));

    // Loop over all possible domain blocks
    for (int i = 0; i < originalImage.rows; i += block_size)
    {
        for (int j = 0; j < originalImage.cols; j += block_size)
        {
            // Extract current domain block from the original image
            Mat domain_block = originalImage(Rect(j, i, block_size, block_size));

            // Initialize variables to track the minimum absolute difference and the coordinates of the closest range block
            double min_abs_diff = numeric_limits<double>::max();
            int closest_x = -1;
            int closest_y = -1;
            int closest_rotation = -1;
            int closest_flipcode = -1;

            // Loop over all possible range blocks in the resized image
            for (int r = 0; r <= resizedImage.rows - block_size; ++r)
            {
                for (int c = 0; c <= resizedImage.cols - block_size; ++c)
                {
                    // Extract current range block from the resized image
                    Mat range_block = resizedImage(Rect(c, r, block_size, block_size));

                    // Loop over all possible rotations (0, 90, 180, 270 degrees)
                    for (int rotation = 0; rotation < 360; rotation += 90)
                    {
                        // Loop over all possible flip codes (0, 1, -1)
                        for (int flipcode = -2; flipcode <= 1; ++flipcode)
                        {
                            // Create a copy of the range block
                            Mat transformed_block = range_block.clone();

                            // Rotate the range block
                            rotateBlock(transformed_block, transformed_block, rotation);

                            // Flip the range block
                            if(flipcode > -2) flipBlock(transformed_block, transformed_block, flipcode);

                            // Calculate the absolute difference between the domain block and the transformed range block
                            double abs_diff = calculateAbsoluteDifference(domain_block, transformed_block);

                            // Update the minimum absolute difference and the coordinates of the closest range block
                            if (abs_diff < min_abs_diff)
                            {
                                min_abs_diff = abs_diff;
                                closest_x = c;
                                closest_y = r;
                                closest_rotation = rotation;
                                closest_flipcode = flipcode;
                            }
                        }
                    }
                }
            }

            // Store the coordinates and transformations of the closest range block for the current domain block
            closest_blocks[i / block_size][j / block_size][0] = closest_x;
            closest_blocks[i / block_size][j / block_size][1] = closest_y;
            closest_blocks[i / block_size][j / block_size][2] = closest_rotation;
            closest_blocks[i / block_size][j / block_size][3] = closest_flipcode;
        }
    }

    // Output the coordinates and transformations of the closest range block for each domain block
    for (int i = 0; i < closest_blocks.size(); ++i)
    {
        for (int j = 0; j < closest_blocks[0].size(); ++j)
        {
            cout << "[" << closest_blocks[i][j][0] << "," << closest_blocks[i][j][1] << "," << closest_blocks[i][j][2] << "," << closest_blocks[i][j][3] << "] ";
        }
        cout << endl;
    }

    return 0;
}
