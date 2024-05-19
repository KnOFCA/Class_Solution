import random
import numpy as np

class QLearning(object):
    def __init__(self, state_size, action_size, learning_rate=0.1, discount_factor=0.99, epsilon=1.0, epsilon_decay=0.995, epsilon_min=0.01):
        self.state_size = state_size
        self.action_size = action_size
        self.learning_rate = 0.1  # 确保 learning_rate 是浮点数
        self.discount_factor = 0.99  # 确保 discount_factor 是浮点数
        self.epsilon = 0.5  # 确保 epsilon 是浮点数
        self.epsilon_decay = 0.995  # 确保 epsilon_decay 是浮点数
        self.epsilon_min = 0.01  # 确保 epsilon_min 是浮点数
        self.Q_table = np.zeros((state_size, action_size))  # 初始化Q表格

    def choose_action(self, state):
        # Implement ε-greedy policy for action selection
        if np.random.rand() <= self.epsilon:
            return random.choice(range(self.action_size))  # Explore: random action
        else:
            return np.argmax(self.Q_table[state])  # Exploit: best action from Q-table
        
    def predict(self, state):
        # Return the action with the highest Q-value for the given state
        return np.argmax(self.Q_table[state])
        
    def update(self, state, action, reward, next_state, done):
        # Q-Learning update rule
        best_next_action = np.argmax(self.Q_table[next_state])
        td_target = reward + self.discount_factor * self.Q_table[next_state, best_next_action] * (not done)
        td_error = td_target - self.Q_table[state, action]
        self.Q_table[state, action] += self.learning_rate * td_error

        # Decay epsilon to reduce exploration over time
        if done:
            self.epsilon = max(self.epsilon_min, self.epsilon * self.epsilon_decay)

    def save(self, path):
        np.save(path + "Q_table.npy", self.Q_table)

    def load(self, path):
        self.Q_table = np.load(path + "Q_table.npy")
