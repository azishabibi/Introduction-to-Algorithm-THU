import numpy as np
import matplotlib.pyplot as plt
import skimage.io
import skimage.color
import skimage.util
#import imageio
#from skimage import color, io, util
#from time import time


def energy_function(image):
    gray_image = skimage.color.rgb2gray(image)
    gradient = np.gradient(gray_image)
    return np.absolute(gradient[0]) + np.absolute(gradient[1])


def compute_cost(image, energy, axis=1):
    energy = energy.copy()

    if axis == 0:
        energy = np.transpose(energy, (1, 0))

    H, W = energy.shape

    cost = np.zeros((H, W))
    paths = np.zeros((H, W), dtype=np.int64)

    # Initialization
    cost[0] = energy[0]
    paths[0] = 0

    for row in range(1, H):
        l = np.insert(cost[row - 1, 0:W - 1], 0, 1e10, axis=0)
        m = cost[row - 1, :]
        r = np.insert(cost[row - 1, 1:W], W - 1, 1e10, axis=0)
        upchoices = np.concatenate((l, m, r), axis=0).reshape(3, -1)

        # M(i, j) = e(i, j) + min(M(i -1 , j - 1), M(i - 1, j), M(i - 1, j + 1))
        cost[row] = energy[row] + np.min(upchoices, axis=0)

        # left = -1
        # middle = 0
        # right = 1
        paths[row] = np.argmin(upchoices, axis=0) - 1

    if axis == 0:
        cost = np.transpose(cost, (1, 0))
        paths = np.transpose(paths, (1, 0))

    return cost, paths


def backtrack_seam(paths, end):
    H, W = paths.shape
    seam = - np.ones(H, dtype=np.int64)

    seam[H - 1] = end

    for h in range(H - 1, 0, -1):
        seam[h - 1] = seam[h] + paths[h, end]
        end += paths[h, end]

    return seam


def remove_seam(image, seam):
    if len(image.shape) == 2:
        image = np.expand_dims(image, axis=2)

    H, W, C = image.shape

    mask = np.ones_like(image, bool)
    for h in range(H):
        mask[h, seam[h]] = False
    out = image[mask].reshape(H, W - 1, C)
    out = np.squeeze(out)

    return out


def reduce(image, size, axis=1, efunc=energy_function, cfunc=compute_cost):
    out = np.copy(image)
    if axis == 0:
        out = np.transpose(out, (1, 0, 2))

    while out.shape[1] > size:
        energy = efunc(out)
        costs, paths = cfunc(out, energy)
        end = np.argmin(costs[-1])
        seam = backtrack_seam(paths, end)
        out = remove_seam(out, seam)

    if axis == 0:
        out = np.transpose(out, (1, 0, 2))

    return out

def find_seams(image, k, axis=1, efunc=energy_function, cfunc=compute_cost):
    image = np.copy(image)
    if axis == 0:
        image = np.transpose(image, (1, 0, 2))

    H, W, C = image.shape
    indices = np.tile(range(W), (H, 1))
    seams = np.zeros((H, W), dtype=int)

    for i in range(k):
        # Get the current optimal seam
        energy = efunc(image)
        cost, paths = cfunc(image, energy)
        end = np.argmin(cost[H - 1])
        seam = backtrack_seam(paths, end)

        # Remove that seam from the image
        image = remove_seam(image, seam)

        # Store the new seam with value i+1 in the image
        seams[np.arange(H), indices[np.arange(H), seam]] = i + 1

        # Remove the indices used by the seam, so that `indices` keep the same shape as `image`
        indices = remove_seam(indices, seam)

    if axis == 0:
        seams = np.transpose(seams, (1, 0))

    return seams


s=input("infile: ")
t=input("outfile: ")
#func=input("func: ")
#rate=input("scaling")
pic = skimage.io.imread(s)
pic = skimage.util.img_as_float(pic)
plt.subplot(1, 2, 1)
plt.imshow(pic)
out = reduce(pic, pic.shape[1]/2)
out = np.rot90(out, 1, (0, 1))
out1 = reduce(out, out.shape[1]/2)
out1 = np.rot90(out1, 3, (0, 1))
plt.subplot(1, 2, 2)
plt.imshow(out1)
skimage.io.imsave(t, out1)
plt.show()
#
# pyinstaller - -add-data 'C:users\liu\appdata\local\programs\python\python39\Lib\site-packages\matplotlib\mpl-data;mpl-data' test3.py
