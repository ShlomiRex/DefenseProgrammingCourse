Rainfull_mi = "45, 65, 70.4, 82.6, 20.1, 90.8, 76.1, 30.92, 46.8, 67.1, 79.9"
months_rainy_num = 0
for mm_str in Rainfull_mi.split(", "):
    mm_float = float(mm_str)
    if mm_float > 75:
        months_rainy_num += 1
print(months_rainy_num)
