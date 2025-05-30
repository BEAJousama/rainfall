# Loop from -2^30 to 9 to ensure we cover wide enough negative range
for x in range(-2**30, 10):
    result = (x * 4) & 0xFFFFFFFF  # simulate unsigned 32-bit
    if result == 44:
        print(f"Found: {x}, x * 4 (unsigned) = {result}")
        break
