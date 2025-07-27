import numpy as np
from typing import Callable, Tuple, List
import random

class GeneticAlgorithm:
    def __init__(
        self,
        fitness_func: Callable,
        bounds: Tuple[Tuple[float, float], Tuple[float, float]],
        population_size: int = 100,
        generations: int = 100,
        mutation_rate: float = 0.1,
        crossover_rate: float = 0.8,
        encoding: str = 'real',
        crossover_type: str = 'arithmetic',
        blx_alpha: float = 0.5
    ):
        self.fitness_func = fitness_func
        self.bounds = bounds
        self.population_size = population_size
        self.generations = generations
        self.mutation_rate = mutation_rate
        self.crossover_rate = crossover_rate
        self.encoding = encoding
        self.crossover_type = crossover_type
        self.blx_alpha = blx_alpha
        
        self.bits_per_variable = 16
        self.total_bits = self.bits_per_variable * 2

    def _initialize_population(self) -> np.ndarray:
        if self.encoding == 'binary':
            return np.random.randint(2, size=(self.population_size, self.total_bits))
        else:
            return np.random.uniform(
                low=[self.bounds[0][0], self.bounds[1][0]],
                high=[self.bounds[0][1], self.bounds[1][1]],
                size=(self.population_size, 2)
            )

    def _binary_to_real(self, binary: np.ndarray) -> np.ndarray:
        x_bin = binary[:self.bits_per_variable]
        y_bin = binary[self.bits_per_variable:]
        x = self.bounds[0][0] + (self.bounds[0][1] - self.bounds[0][0]) * int(''.join(map(str, x_bin)), 2) / (2**self.bits_per_variable - 1)
        y = self.bounds[1][0] + (self.bounds[1][1] - self.bounds[1][0]) * int(''.join(map(str, y_bin)), 2) / (2**self.bits_per_variable - 1)
        return np.array([x, y])

    def _evaluate_fitness(self, individual: np.ndarray) -> float:
        values = self._binary_to_real(individual) if self.encoding == 'binary' else individual
        return self.fitness_func(values[0], values[1])

    def _select_parents(self, fitness_values: np.ndarray) -> Tuple[int, int]:
        def tournament():
            contenders = np.random.choice(len(fitness_values), 3, replace=False)
            return contenders[np.argmin(fitness_values[contenders])]
        return tournament(), tournament()

    def _binary_crossover(self, p1: np.ndarray, p2: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        if random.random() > self.crossover_rate:
            return p1.copy(), p2.copy()
        if self.crossover_type == '1point':
            pt = random.randint(1, self.total_bits - 1)
            return np.concatenate([p1[:pt], p2[pt:]]), np.concatenate([p2[:pt], p1[pt:]])
        pt1 = random.randint(1, self.total_bits - 2)
        pt2 = random.randint(pt1 + 1, self.total_bits - 1)
        return (
            np.concatenate([p1[:pt1], p2[pt1:pt2], p1[pt2:]]),
            np.concatenate([p2[:pt1], p1[pt1:pt2], p2[pt2:]])
        )

    def _real_crossover(self, p1: np.ndarray, p2: np.ndarray) -> Tuple[np.ndarray, np.ndarray]:
        if random.random() > self.crossover_rate:
            return p1.copy(), p2.copy()
        if self.crossover_type == 'arithmetic':
            alpha = random.random()
            return alpha * p1 + (1 - alpha) * p2, (1 - alpha) * p1 + alpha * p2
        d = np.abs(p1 - p2)
        min_val = np.minimum(p1, p2) - self.blx_alpha * d
        max_val = np.maximum(p1, p2) + self.blx_alpha * d
        return np.random.uniform(min_val, max_val), np.random.uniform(min_val, max_val)

    def _mutate(self, individual: np.ndarray) -> np.ndarray:
        if self.encoding == 'binary':
            mutation_mask = np.random.rand(self.total_bits) < self.mutation_rate
            individual[mutation_mask] = 1 - individual[mutation_mask]
        else:
            mutation_mask = np.random.rand(2) < self.mutation_rate
            individual[mutation_mask] += np.random.normal(0, 0.1, 2)[mutation_mask]
            individual[0] = np.clip(individual[0], *self.bounds[0])
            individual[1] = np.clip(individual[1], *self.bounds[1])
        return individual

    def optimize(self) -> Tuple[np.ndarray, float, List[float]]:
        population = self._initialize_population()
        best_fitness = float('inf')
        best_solution = None
        history = []

        for _ in range(self.generations):
            fitness_values = np.array([self._evaluate_fitness(ind) for ind in population])
            gen_best_idx = np.argmin(fitness_values)

            if fitness_values[gen_best_idx] < best_fitness:
                best_fitness = fitness_values[gen_best_idx]
                best_solution = population[gen_best_idx].copy()

            history.append(best_fitness)

            new_population = []
            while len(new_population) < self.population_size:
                i1, i2 = self._select_parents(fitness_values)
                p1, p2 = population[i1], population[i2]

                if self.encoding == 'binary':
                    c1, c2 = self._binary_crossover(p1, p2)
                else:
                    c1, c2 = self._real_crossover(p1, p2)

                new_population.extend([self._mutate(c1), self._mutate(c2)])

            population = np.array(new_population[:self.population_size])

        if self.encoding == 'binary':
            best_solution = self._binary_to_real(best_solution)

        return best_solution, best_fitness, history
