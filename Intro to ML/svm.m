clc
clear all
close all

images = loadMNISTImages('../MNIST_Dataset/train-images.idx3-ubyte');
labels = loadMNISTLabels('../MNIST_Dataset/train-labels.idx1-ubyte');

test_images = loadMNISTImages('../MNIST_Dataset/t10k-images.idx3-ubyte');
test_labels = loadMNISTLabels('../MNIST_Dataset/t10k-labels.idx1-ubyte');

images_T = transpose(images);
test_images_T = transpose(test_images);

dataset = [images_T labels];

Mdl = fitcecoc(images_T,labels);

test_predict = predict(Mdl, test_images_T);