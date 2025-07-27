import numpy as np
import pandas as pd
from scipy import stats
import matplotlib.pyplot as plt
import seaborn as sns
from benchmark_functions import BenchmarkFunctions
from genetic_algorithm import GeneticAlgorithm

def run_experiment(
    fitness_func,
    bounds,
    encoding,
    crossover_type,
    n_runs=30,
    max_evaluations=10000  # Fixed number of evaluations
):
    """
    Run multiple experiments with the same configuration
    
    Args:
        fitness_func: The objective function to optimize
        bounds: Search space bounds
        encoding: 'binary' or 'real'
        crossover_type: Type of crossover operator
        n_runs: Number of independent runs
        max_evaluations: Fixed number of fitness evaluations
    
    Returns:
        Array of best fitness values from each run
    """
    results = []
    
    # Calculate population size and generations to achieve fixed evaluations
    population_size = 100
    generations = max_evaluations // population_size
    
    for run in range(n_runs):
        print(f"  Run {run + 1}/{n_runs}")
        ga = GeneticAlgorithm(
            fitness_func=fitness_func,
            bounds=bounds,
            population_size=population_size,
            generations=generations,
            encoding=encoding,
            crossover_type=crossover_type,
            mutation_rate=0.1,
            crossover_rate=0.8
        )
        best_solution, best_fitness, _ = ga.optimize()
        results.append(best_fitness)
    
    return np.array(results)

def perform_comprehensive_statistical_analysis(results_dict):
    """
    Perform comprehensive statistical analysis including multiple test types
    
    Args:
        results_dict: Dictionary with configuration names as keys and results arrays as values
    
    Returns:
        Tuple of (summary_stats, statistical_tests_results)
    """
    # Prepare data for analysis
    data = []
    for config, results in results_dict.items():
        for result in results:
            data.append({
                'Configuration': config,
                'Fitness': result
            })
    df = pd.DataFrame(data)
    
    # Summary statistics
    summary = df.groupby('Configuration')['Fitness'].agg([
        'count', 'mean', 'std', 'min', 'max', 'median'
    ]).round(6)
    
    # Statistical tests
    configs = list(results_dict.keys())
    n_configs = len(configs)
    
    # Initialize results storage
    statistical_tests = {
        'mann_whitney': np.zeros((n_configs, n_configs)),
        't_test': np.zeros((n_configs, n_configs)),
        'wilcoxon': np.zeros((n_configs, n_configs))
    }
    
    # Pairwise comparisons
    for i in range(n_configs):
        for j in range(i+1, n_configs):
            data1 = results_dict[configs[i]]
            data2 = results_dict[configs[j]]
            
            # Mann-Whitney U test (non-parametric)
            try:
                stat, p_val = stats.mannwhitneyu(data1, data2, alternative='two-sided')
                statistical_tests['mann_whitney'][i, j] = p_val
                statistical_tests['mann_whitney'][j, i] = p_val
            except:
                statistical_tests['mann_whitney'][i, j] = np.nan
                statistical_tests['mann_whitney'][j, i] = np.nan
            
            # Independent t-test (parametric)
            try:
                stat, p_val = stats.ttest_ind(data1, data2)
                statistical_tests['t_test'][i, j] = p_val
                statistical_tests['t_test'][j, i] = p_val
            except:
                statistical_tests['t_test'][i, j] = np.nan
                statistical_tests['t_test'][j, i] = np.nan
            
            # Wilcoxon rank-sum test (alternative to Mann-Whitney)
            try:
                stat, p_val = stats.ranksums(data1, data2)
                statistical_tests['wilcoxon'][i, j] = p_val
                statistical_tests['wilcoxon'][j, i] = p_val
            except:
                statistical_tests['wilcoxon'][i, j] = np.nan
                statistical_tests['wilcoxon'][j, i] = np.nan
    
    # ANOVA test (if more than 2 groups)
    if len(configs) > 2:
        try:
            f_stat, anova_p = stats.f_oneway(*[results_dict[config] for config in configs])
            statistical_tests['anova'] = {'f_statistic': f_stat, 'p_value': anova_p}
        except:
            statistical_tests['anova'] = {'f_statistic': np.nan, 'p_value': np.nan}
    
    return summary, statistical_tests, configs

def plot_comprehensive_results(results_dict, title, save_prefix=""):
    """
    Create comprehensive visualization of results
    
    Args:
        results_dict: Dictionary with results
        title: Plot title
        save_prefix: Prefix for saved files
    """
    # Box plot
    plt.figure(figsize=(12, 6))
    data = []
    labels = []
    for config, results in results_dict.items():
        data.append(results)
        labels.append(config.replace('_', '\n'))  # Better formatting
    
    box_plot = plt.boxplot(data, labels=labels, patch_artist=True)
    
    # Color the boxes
    colors = ['lightblue', 'lightgreen', 'lightcoral', 'lightyellow']
    for patch, color in zip(box_plot['boxes'], colors):
        patch.set_facecolor(color)
    
    plt.title(f'{title} - Box Plot Comparison')
    plt.ylabel('Fitness Value')
    plt.xticks(rotation=0)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    if save_prefix:
        plt.savefig(f'{save_prefix}_boxplot.png', dpi=300, bbox_inches='tight')
    plt.show()
    
    # Violin plot for distribution visualization
    plt.figure(figsize=(12, 6))
    
    # Prepare data for seaborn
    plot_data = []
    for config, results in results_dict.items():
        for result in results:
            plot_data.append({'Configuration': config.replace('_', '\n'), 'Fitness': result})
    
    plot_df = pd.DataFrame(plot_data)
    
    sns.violinplot(data=plot_df, x='Configuration', y='Fitness')
    plt.title(f'{title} - Distribution Comparison')
    plt.ylabel('Fitness Value')
    plt.xticks(rotation=0)
    plt.grid(True, alpha=0.3)
    plt.tight_layout()
    
    if save_prefix:
        plt.savefig(f'{save_prefix}_violin.png', dpi=300, bbox_inches='tight')
    plt.show()

def generate_report_tables(summary, statistical_tests, configs, function_name):
    """
    Generate formatted tables for the report
    
    Args:
        summary: Summary statistics DataFrame
        statistical_tests: Dictionary of statistical test results
        configs: List of configuration names
        function_name: Name of the optimization function
    """
    print(f"Result for {function_name.upper()} function:")
    
    print("\nStatistics Summary:")
    print(summary.to_string())
    
    print(f"\nStatistical test (p-values):")
    
    for test_name, p_matrix in statistical_tests.items():
        if test_name == 'anova':
            print(f"\nAnova Test:")
            print(f"F-statistic: {p_matrix['f_statistic']:.6f}")
            print(f"p-value: {p_matrix['p_value']:.6f}")
            if p_matrix['p_value'] < 0.05:
                print("Result: Significant differences detected between configurations")
            else:
                print("Result: No significant differences detected between configurations")
        else:
            print(f"\n{test_name.replace('_', ' ').title()} Test:")
            if isinstance(p_matrix, np.ndarray):
                p_df = pd.DataFrame(p_matrix, index=configs, columns=configs)
                print(p_df.round(6).to_string())
                
                # Highlight significant differences
                significant_pairs = []
                for i in range(len(configs)):
                    for j in range(i+1, len(configs)):
                        if p_matrix[i, j] < 0.05:
                            significant_pairs.append(f"{configs[i]} vs {configs[j]}")
                
                if significant_pairs:
                    print(f"Significant differences (p < 0.05): {', '.join(significant_pairs)}")
                else:
                    print("No significant differences found (p < 0.05)")

def main():
    """Main experiment runner"""
    # Configuration matrix
    configurations = [
        ('binary', '1point'),
        ('binary', '2point'),
        ('real', 'arithmetic'),
        ('real', 'blx')
    ]
    
    # Test functions with their properties
    functions = [
        (BenchmarkFunctions.rastrigin, [(-5.12, 5.12), (-5.12, 5.12)], "Rastrigin"),
        (BenchmarkFunctions.ackley, [(-32.768, 32.768), (-32.768, 32.768)], "Ackley")
    ]
    
    # Fixed number of fitness evaluations for fair comparison
    MAX_EVALUATIONS = 10000
    N_RUNS = 30
    
    print(f"Starting experiments with {MAX_EVALUATIONS} fitness evaluations per run")
    print(f"Each configuration will be tested {N_RUNS} times\n")
    
    for fitness_func, bounds, func_name in functions:
        print(f"Optimizing {func_name.upper()} function")
        print(f"Domain: x ∈ [{bounds[0][0]}, {bounds[0][1]}], y ∈ [{bounds[1][0]}, {bounds[1][1]}]")
        
        results_dict = {}
        
        for encoding, crossover_type in configurations:
            config_name = f"{encoding}_{crossover_type}"
            print(f"\nRunning configuration: {config_name}")
            
            results = run_experiment(
                fitness_func,
                bounds,
                encoding,
                crossover_type,
                n_runs=N_RUNS,
                max_evaluations=MAX_EVALUATIONS
            )
            results_dict[config_name] = results
            
            print(f"  Best result: {np.min(results):.6f}")
            print(f"  Mean result: {np.mean(results):.6f}")
            print(f"  Std deviation: {np.std(results):.6f}")
        
        summary, statistical_tests, configs = perform_comprehensive_statistical_analysis(results_dict)
        
        generate_report_tables(summary, statistical_tests, configs, func_name)

        plot_comprehensive_results(results_dict, f"{func_name} Function Results", 
                                 save_prefix=func_name.lower())
        
        print(f"\nCompleted analysis for {func_name} function")
        print("Results saved as PNG files")

if __name__ == "__main__":
    main()