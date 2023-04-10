from config import path_to_file1, path_to_file2
import struct


def read_weight_matrix(filename):
    with open(filename, 'rb') as file:

        dim = struct.unpack('i', file.read(4))
        matrix = []

        for i in range(*dim):
            list1 = []
            for j in range(*dim):
                integer_from_file = struct.unpack('i', file.read(4))
                list1.append(*integer_from_file)
            matrix.append(list1)

        file.close()

    return matrix


def print_weight_matrix(matrix):
    for i in range(len(matrix)):
        print(matrix[i])



