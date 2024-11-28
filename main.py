import re
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D, art3d
from matplotlib.patches import Circle
from matplotlib.animation import FuncAnimation

output_file = 'simulation_output.txt'

time_steps = []
positions = []
angular_momentum = []

time_pattern = re.compile(r't = (\d+\.\d+|\d+)')
position_pattern = re.compile(r'Position = \(([-\d\.]+), ([-\d\.]+), ([-\d\.]+)\)')
L_pattern = re.compile(r'L = \(([-\d\.]+), ([-\d\.]+), ([-\d\.]+)\)')

with open(output_file, 'r') as file:
    for line in file:
        time_match = time_pattern.search(line)
        pos_match = position_pattern.search(line)
        L_match = L_pattern.search(line)

        if time_match:
            time_steps.append(float(time_match.group(1)))
        if pos_match:
            positions.append([float(pos_match.group(1)), float(pos_match.group(2)), float(pos_match.group(3))])
        if L_match:
            angular_momentum.append([float(L_match.group(1)), float(L_match.group(2)), float(L_match.group(3))])

positions = np.array(positions)
angular_momentum = np.array(angular_momentum)

def rotation_matrix_from_axis_angle(axis, angle):
    axis = axis / np.linalg.norm(axis)
    cos_a = np.cos(angle)
    sin_a = np.sin(angle)
    one_minus_cos = 1 - cos_a
    x, y, z = axis
    return np.array([
        [cos_a + x*x*one_minus_cos, x*y*one_minus_cos - z*sin_a, x*z*one_minus_cos + y*sin_a],
        [y*x*one_minus_cos + z*sin_a, cos_a + y*y*one_minus_cos, y*z*one_minus_cos - x*sin_a],
        [z*x*one_minus_cos - y*sin_a, z*y*one_minus_cos + x*sin_a, cos_a + z*z*one_minus_cos]
    ])

# Plot the rotor as a disk oriented according to L
def plot_disk(ax, center, normal, radius=0.1, color='orange'):
    theta = np.linspace(0, 2 * np.pi, 41)
    circle_points = np.vstack((radius * np.cos(theta), radius * np.sin(theta), np.zeros_like(theta)))

    direction = np.array([0, 0, 1])  
    normal = np.array(normal) / np.linalg.norm(normal)
    if not np.allclose(normal, direction):
        rotation_axis = np.cross(direction, normal)
        rotation_angle = np.arccos(np.dot(direction, normal))
        rotation_matrix = rotation_matrix_from_axis_angle(rotation_axis, rotation_angle)
        circle_points = rotation_matrix.dot(circle_points)

    circle_points += np.array(center).reshape(3, 1)

    ax.plot(circle_points[0], circle_points[1], circle_points[2], color=color)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(-2, 2)
ax.set_ylim(-2, 2)
ax.set_zlim(0, 1)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

def update_plot(i):
    ax.cla()  
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_zlim(0, 1)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    pos = positions[i]
    L = angular_momentum[i]

    
    plot_disk(ax, pos, L)

    # Plot vectors for position and L vectors
    ax.quiver(0, 0, 0, pos[0], pos[1], pos[2], color='blue', label='Position')
    ax.quiver(0, 0, 0, L[0], L[1], L[2], color='red', label='Angular Momentum (L)')
    
    ax.legend()
    ax.set_title(f'Time = {time_steps[i]:.2f}s')

ani = FuncAnimation(fig, update_plot, frames=len(time_steps), interval=200)  
plt.show()
ani.save("gyroscope_animation.gif", writer="imagemagick", fps=10)
