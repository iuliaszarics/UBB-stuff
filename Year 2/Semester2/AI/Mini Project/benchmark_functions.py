import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

class BenchmarkFunctions:
    @staticmethod
    def rastrigin(x, y):
        A = 10
        return A * 2 + (x**2 - A * np.cos(2 * np.pi * x)) + (y**2 - A * np.cos(2 * np.pi * y))

    @staticmethod
    def ackley(x, y):
        a, b, c = 20, 0.2, 2 * np.pi
        term1 = -a * np.exp(-b * np.sqrt(0.5 * (x**2 + y**2)))
        term2 = -np.exp(0.5 * (np.cos(c * x) + np.cos(c * y)))
        return term1 + term2 + a + np.exp(1)

    @staticmethod
    def plot_2d_contour(func, title, x_range, y_range, levels=50):
        x = np.linspace(x_range[0], x_range[1], 100)
        y = np.linspace(y_range[0], y_range[1], 100)
        X, Y = np.meshgrid(x, y)
        Z = func(X, Y)
        plt.figure(figsize=(8, 6))
        cp = plt.contourf(X, Y, Z, levels=levels, cmap='viridis')
        plt.colorbar(cp)
        plt.title(title)
        plt.xlabel("x")
        plt.ylabel("y")
        return plt

    @staticmethod
    def plot_3d_surface(func, title, x_range, y_range):
        x = np.linspace(x_range[0], x_range[1], 100)
        y = np.linspace(y_range[0], y_range[1], 100)
        X, Y = np.meshgrid(x, y)
        Z = func(X, Y)
        fig = plt.figure(figsize=(10, 8))
        ax = fig.add_subplot(111, projection='3d')
        surf = ax.plot_surface(X, Y, Z, cmap='viridis')
        fig.colorbar(surf)
        ax.set_title(title)
        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_zlabel('f(x,y)')
        return plt

if __name__ == "__main__":
    BenchmarkFunctions.plot_2d_contour(BenchmarkFunctions.rastrigin, "rastrigin (2D)", [-5.12, 5.12], [-5.12, 5.12]).show()
    BenchmarkFunctions.plot_3d_surface(BenchmarkFunctions.rastrigin, "rastrigin (3D)", [-5.12, 5.12], [-5.12, 5.12]).show()
    BenchmarkFunctions.plot_2d_contour(BenchmarkFunctions.ackley, "ackley (2D)", [-32.768, 32.768], [-32.768, 32.768]).show()
    BenchmarkFunctions.plot_3d_surface(BenchmarkFunctions.ackley, "ackley (3D)", [-32.768, 32.768], [-32.768, 32.768]).show()
