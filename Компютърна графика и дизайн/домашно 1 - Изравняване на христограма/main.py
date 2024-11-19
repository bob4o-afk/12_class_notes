def histogram_equalization(image):
    # Step 1: Calculate the histogram of the image
    histogram = [0] * 256
    for row in image:
        for pixel in row:
            histogram[pixel] += 1

    # Step 2: Calculate the cumulative distribution function (CDF)
    cdf = [0] * 256
    cdf[0] = histogram[0]
    for i in range(1, 256):
        cdf[i] = cdf[i - 1] + histogram[i]

    # Normalize the CDF
    cdf_min = min([v for v in cdf if v > 0])  # Minimum non-zero CDF value
    total_pixels = len(image) * len(image[0])  # Total number of pixels
    L = 256

    # Step 3: Calculate new pixel values using the formula
    new_pixel_values = [0] * 256
    for v in range(256):
        if cdf[v] > 0:
            # Apply the normalization formula
            new_pixel_values[v] = round((cdf[v] - cdf_min) / (total_pixels - cdf_min) * (L - 1))

    # Step 4: Apply new pixel values to generate the equalized image
    equalized_image = []
    for row in image:
        new_row = []
        for pixel in row:
            new_row.append(new_pixel_values[pixel])
        equalized_image.append(new_row)

    return equalized_image


image_array = [
    [52, 55, 61, 59, 79, 61, 76, 61],
    [62, 59, 55, 104, 94, 85, 59, 71],
    [63, 65, 66, 113, 144, 104, 63, 72],
    [64, 70, 70, 126, 154, 109, 71, 69],
    [67, 73, 68, 106, 122, 88, 68, 68],
    [68, 79, 60, 70, 77, 66, 58, 75],
    [69, 85, 64, 58, 55, 61, 65, 83],
    [70, 87, 69, 68, 65, 73, 78, 90]
]

equalized_image = histogram_equalization(image_array)

for row in equalized_image:
    print("\t".join(map(str, row)))
