import tkinter as tk
from tkinter import messagebox

def bresenham_line(x1, y1, x2, y2):
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    sx = 1 if x1 < x2 else -1
    sy = 1 if y1 < y2 else -1

    err = dx - dy

    points = []

    while True:
        points.append((x1, y1))

        if x1 == x2 and y1 == y2:
            break

        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x1 += sx
        if e2 < dx:
            err += dx
            y1 += sy

    return points

def visualize_line(points):
    root = tk.Tk()
    root.title("Bresenham Line Visualization")

    canvas = tk.Canvas(root, width=800, height=600, bg="white")
    canvas.pack()

    for i in range(0, 800, 20):
        canvas.create_line(i, 0, i, 600, fill="lightgray")
    for j in range(0, 600, 20):
        canvas.create_line(0, j, 800, j, fill="lightgray")

    for x, y in points:
        canvas.create_rectangle(x * 20 + 400, y * 20 + 300, x * 20 + 420, y * 20 + 320, fill="orange", outline="black")

    x1, y1 = points[0]
    x2, y2 = points[-1]
    canvas.create_line(x1 * 20 + 410, y1 * 20 + 310, x2 * 20 + 410, y2 * 20 + 310, fill="black", width=3)

    def on_close():
        if messagebox.askokcancel("Quit", "Do you want to quit?"):
            root.destroy()

    root.protocol("WM_DELETE_WINDOW", on_close)
    root.mainloop()

if __name__ == "__main__":
    x_start, y_start = 0, 0
    x_end, y_end = 10, 6

    line_points = bresenham_line(x_start, y_start, x_end, y_end)

    visualize_line(line_points)
