import re
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D, art3d
from matplotlib.patches import Circle
from matplotlib.animation import FuncAnimation

# Path to your output file
output_file = 'simulation_output.txt'

# Initialize lists to store parsed data
time_steps = []
positions = []
angular_momentum = []
tau = []

# Regular expression patterns to extract data
time_pattern = re.compile(r't = (\d+\.\d+|\d+)')
position_pattern = re.compile(r'Position = \(([-\d\.]+), ([-\d\.]+), ([-\d\.]+)\)')
L_pattern = re.compile(r'L = \(([-\d\.]+), ([-\d\.]+), ([-\d\.]+)\)')
tau_pattern = re.compile(r'tau = \(([-\d\.]+), ([-\d\.]+), ([-\d\.]+)\)')

# Read and parse the file
with open(output_file, 'r') as file:
    for line in file:
        time_match = time_pattern.search(line)
        pos_match = position_pattern.search(line)
        L_match = L_pattern.search(line)
        tau_match = tau_pattern.search(line)

        if time_match:
            time_steps.append(float(time_match.group(1)))
        if pos_match:
            positions.append([float(pos_match.group(1)), float(pos_match.group(2)), float(pos_match.group(3))])
        if L_match:
            angular_momentum.append([float(L_match.group(1)), float(L_match.group(2)), float(L_match.group(3))])
        if tau_match:
            tau.append([float(tau_match.group(1)), float(tau_match.group(2)), float(tau_match.group(3))])

# Convert lists to numpy arrays for easier manipulation
positions = np.array(positions)
angular_momentum = np.array(angular_momentum)
tau = np.array(tau)

# Helper function to create a rotation matrix from an axis and angle
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

# Function to plot a disk representing the rotor at each position and orientation
def plot_disk(ax, center, normal, radius=0.1, color='orange'):
    # Generate points on a circle in the xy-plane
    theta = np.linspace(0, 2 * np.pi, 41)
    circle_points = np.vstack((radius * np.cos(theta), radius * np.sin(theta), np.zeros_like(theta)))

    # Create a rotation matrix to align the circle with the normal vector
    direction = np.array([0, 0, 1])  # Default normal for circle in the z direction
    normal = np.array(normal) / np.linalg.norm(normal)
    if not np.allclose(normal, direction):
        rotation_axis = np.cross(direction, normal)
        rotation_angle = np.arccos(np.dot(direction, normal))
        rotation_matrix = rotation_matrix_from_axis_angle(rotation_axis, rotation_angle)
        circle_points = rotation_matrix.dot(circle_points)

    # Translate the circle points to the center position
    circle_points += np.array(center).reshape(3, 1)

    # Plot the rotated circle points as a patch in 3D
    ax.plot(circle_points[0], circle_points[1], circle_points[2], color=color)

# Set up the 3D plot for animation
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlim(-2, 2)
ax.set_ylim(-2, 2)
ax.set_zlim(0, 1)
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')

# Animation update function
def update_plot(i):
    ax.cla()  # Clear previous drawings
    horizontal_limit = positions[0][0]
    vertical_limit = positions[0][2]
    ax.set_xlim(-2*horizontal_limit, 2*horizontal_limit)
    ax.set_ylim(-2*horizontal_limit, 2*horizontal_limit)
    ax.set_zlim(0, 2*vertical_limit)
    ax.set_xlabel('X')
    ax.set_ylabel('Y')
    ax.set_zlabel('Z')

    # Use data from parsed file
    pos = positions[i]
    L = angular_momentum[i]
    torque = tau[i]

    # Plot the rotor as a disk oriented according to L
    plot_disk(ax, pos, L)

    # Plot vectors for position and angular momentum
    ax.quiver(0, 0, 0, pos[0], pos[1], pos[2], color='blue', label='Position',arrow_length_ratio=0.1)
    ax.quiver(pos[0],pos[1],pos[2], L[0], L[1], L[2], color='red', label='Angular Momentum (L)',arrow_length_ratio=0.5)
    ax.quiver(pos[0],pos[1],pos[2],torque[0],torque[1],torque[2], color='green', label='Torque (tau)',arrow_length_ratio=0.1)
    ax.legend(loc='lower left')
    ax.set_title(f'Time = {time_steps[i]:.2f}s')

# Create the animation
ani = FuncAnimation(fig, update_plot, frames=len(time_steps), interval=200)  # interval=200 slows down the animation
plt.show()
ani.save("gyroscope_animation.gif", writer="imagemagick", fps=10)