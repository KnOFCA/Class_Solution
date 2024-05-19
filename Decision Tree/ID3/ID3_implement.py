import numpy as np
from collections import Counter
from graphviz import Digraph, Source
import matplotlib.pyplot as plt
import networkx as nx


def entropy(y):
    hist = np.bincount(y)
    ps = hist / len(y)
    return -np.sum([p * np.log2(p) for p in ps if p > 0])


def information_gain(y, x):
    parent_entropy = entropy(y)

    n = len(y)
    child1_mask = x == 0
    n1 = child1_mask.sum()
    n2 = n - n1
    e1 = entropy(y[child1_mask])
    e2 = entropy(y[~child1_mask])
    child_entropy = n1 / n * e1 + n2 / n * e2

    # return the 'gain' of splitting along this feature
    ig = parent_entropy - child_entropy
    return ig


class Node:
    def __init__(self, feature=None, threshold=None, left=None, right=None, *, value=None):
        self.feature = feature
        self.threshold = threshold
        self.left = left
        self.right = right
        self.value = value

    def is_leaf_node(self):
        return self.value is not None


class ID3:
    def __init__(self, min_samples_split=2, max_depth=100, n_feats=None):
        self.min_samples_split = min_samples_split
        self.max_depth = max_depth
        self.n_feats = n_feats
        self.root = None

    def fit(self, X, y):
        """
        Fit
        :param X: Features
        :param y: Labels
        """
        self.n_feats = X.shape[1] if not self.n_feats else min(self.n_feats, X.shape[1])
        self.root = self._grow_tree(X, y)

    def _grow_tree(self, X, y, depth=0):
        """
        Build ID3 tree
        :param X: Features
        :param y: Labels
        :param depth: now depth
        """
        n_samples, n_features = X.shape
        n_labels = len(np.unique(y))

        # stopping criteria
        if (depth >= self.max_depth
                or n_labels == 1
                or n_samples < self.min_samples_split):
            leaf_value = self._most_common_label(y)
            return Node(value=leaf_value)

        feat_idxs = np.random.choice(n_features, self.n_feats, replace=False)

        best_feat, best_thresh = self._best_criteria(X, y, feat_idxs)

        # grow the children that result from the split
        left_idxs, right_idxs = self._split(X[:, best_feat], best_thresh)
        left = self._grow_tree(X[left_idxs, :], y[left_idxs], depth + 1)
        right = self._grow_tree(X[right_idxs, :], y[right_idxs], depth + 1)
        return Node(best_feat, best_thresh, left, right)

    def _best_criteria(self, X, y, feat_idxs):
        """
        Get best spilt
        :param X: Features
        :param y: Labels
        :param feat_idxs: index of input feature for use
        """
        best_gain = -1
        split_idx, split_thresh = None, None
        for feat_idx in feat_idxs:
            X_column = X[:, feat_idx]
            thresholds = np.unique(X_column)
            for threshold in thresholds:
                gain = self._information_gain(y, X_column, threshold)

                if gain > best_gain:
                    best_gain = gain
                    split_idx = feat_idx
                    split_thresh = threshold

        return split_idx, split_thresh

    def _information_gain(self, y, X_column, split_thresh):
        """
        Calculate information gain
        :param y: Labels
        :param X_column: index of input feature to spilt
        :param split_thresh: split_thresh to decide how to spilt
        """
        # parent loss
        parent_entropy = entropy(y)

        # generate split
        left_idxs, right_idxs = self._split(X_column, split_thresh)

        if len(left_idxs) == 0 or len(right_idxs) == 0:
            return 0

        # compute the weighted avg. of the loss for the children
        n = len(y)
        n_l, n_r = len(left_idxs), len(right_idxs)
        e_l, e_r = entropy(y[left_idxs]), entropy(y[right_idxs])
        child_entropy = (n_l / n) * e_l + (n_r / n) * e_r

        # information gain is difference in loss before vs. after split
        ig = parent_entropy - child_entropy
        return ig

    def _split(self, X_column, split_thresh):
        """
        Split into two branch
        :param X_column: index of input feature to spilt
        :param split_thresh: split_thresh: split_thresh to decide how to spilt
        """
        left_idxs = np.argwhere(X_column <= split_thresh).flatten()
        right_idxs = np.argwhere(X_column > split_thresh).flatten()
        return left_idxs, right_idxs

    def _most_common_label(self, y):
        """
        Get the most numbers of label
        :param y: labels
        """
        counter = Counter(y)
        most_common = counter.most_common(1)[0][0]
        return most_common

    def tree_to_dict(self, node=None):
        """
        Convert tree to dict
        :param node: tree root
        """
        if node is None:
            node = self.root

        if node.is_leaf_node():
            return {'value': node.value}

        return {
            'feature': node.feature,
            'threshold': node.threshold,
            'left': self.tree_to_dict(node.left),
            'right': self.tree_to_dict(node.right)
        }

    def draw_tree(self):
        """
        plot tree
        """
        dot = Digraph()
        self._draw_tree_helper(self.root, dot)
        return dot

    def _draw_tree_helper(self, node, dot, parent=None, side=None):
        if node is None:
            return

        node_id = str(id(node))
        if node.is_leaf_node():
            dot.node(node_id, label=str(node.value), shape='box')
        else:
            dot.node(node_id, label=f'Feature {node.feature}\nThreshold {node.threshold}')

        if parent is not None:
            dot.edge(parent, node_id, label=side)

        self._draw_tree_helper(node.left, dot, parent=node_id, side='True')
        self._draw_tree_helper(node.right, dot, parent=node_id, side='False')

    def predict(self, X):
        """
        prediction
        :param X: features
        :return:
        """
        return np.array([self._traverse_tree(x, self.root) for x in X])

    def _traverse_tree(self, x, node):
        """
        For prediction
        :param x: features
        :param node: root of ID3 tree
        :return:
        """
        if node.is_leaf_node():
            return node.value

        if x[node.feature] <= node.threshold:
            return self._traverse_tree(x, node.left)
        return self._traverse_tree(x, node.right)
