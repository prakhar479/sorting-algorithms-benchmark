import sys
import matplotlib.pyplot as plt

def variance(data: list) -> float:
    mean = sum(data) / len(data)
    squared_diffs = [(x - mean) ** 2 for x in data]
    variance = sum(squared_diffs)/len(data)
    return variance**0.5
    
def read_file(file_path: str) -> tuple[dict, list]:
    algorithm_times = {}
    array_sizes = []

    with open(file_path, 'r') as file:
        lines = file.readlines()
        for line in lines:
            if line.startswith('Number of elements:'):
                array_sizes.append(int(line.split(':')[1].strip()))
            elif line.startswith('Sorting algorithm:'):
                algorithm_name = line.split(':')[1].strip()
                if algorithm_name not in algorithm_times:
                    algorithm_times[algorithm_name] = []
            elif line.startswith('Average sorting time:'):
                sorting_time = float(line.split(':')[1].strip().split()[0])
                algorithm_times[algorithm_name].append(sorting_time)       

    return algorithm_times, array_sizes

def plot_line_graph(array_sizes: list, algorithm_times: list, plot_colors: list)-> None:
    algorithms = ['Insertion Sort', 'Merge Sort', 'Quick Sort', 'Shell Sort', 'Tim Sort', 'Radix Sort', 'Comb Sort']
    for i, algorithm in enumerate(algorithms):
        plt.plot(array_sizes, algorithm_times[algorithm], label=algorithm, color=plot_colors[i])

    plt.xlabel('Array Size')
    plt.ylabel('Average Sorting Time (seconds)')
    plt.title('Sorting Algorithm Performance')
    plt.legend()
    plt.grid()
    plt.savefig('results/sorting_algorithm_performance_linear.png')
    plt.show()

def plot_log_graph(array_sizes: list, algorithm_times: list, plot_colors: list) -> None:
    algorithms = ['Insertion Sort', 'Merge Sort', 'Quick Sort', 'Shell Sort', 'Tim Sort', 'Radix Sort', 'Comb Sort']
    for i, algorithm in enumerate(algorithms):
        plt.plot(array_sizes, algorithm_times[algorithm], label=algorithm, color=plot_colors[i])

    plt.xlabel('Array Size')
    plt.ylabel('Average Sorting Time (seconds)')
    plt.title('Sorting Algorithm Performance')
    plt.legend()
    plt.yscale('log')
    plt.grid()
    plt.savefig('results/sorting_algorithm_performance_log.png')
    plt.show()

def plot_bar_graph(algorithm_times: list, plot_colors: list) -> None:
    algorithm_names = list(algorithm_times.keys())
    average_times = [sum(algorithm_times[algorithm_name]) / len(algorithm_times[algorithm_name]) for algorithm_name in algorithm_names]
    var_times = [variance(algorithm_times[algorithm_name]) for algorithm_name in algorithm_names]
    
    plt.bar(algorithm_names, average_times, color=plot_colors)
    plt.errorbar(algorithm_names, average_times, yerr=var_times, fmt='.', color='k')
    plt.xlabel('Sorting Algorithm')
    plt.ylabel('Average Sorting Time (seconds)')
    plt.title('Sorting Algorithm Performance')
    plt.grid()
    plt.savefig('results/sorting_algorithm_performance_aggregated.png')
    plt.show()

if __name__ == '__main__':
    file_path = sys.argv[1]
    algorithm_times, array_sizes = read_file(file_path)

    plot_colors = ['red', 'blue', 'green', 'orange', 'purple', 'brown', 'pink']

    plot_line_graph(array_sizes, algorithm_times, plot_colors)
    plot_log_graph(array_sizes, algorithm_times, plot_colors)
    plot_bar_graph(algorithm_times, plot_colors)
