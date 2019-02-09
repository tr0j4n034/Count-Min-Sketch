# Count-Min-Sketch

Count-Min Sketch and Consistent Weighted Sampling implementation

Quick look:
https://en.wikipedia.org/wiki/Count–min_sketch
https://www.microsoft.com/en-us/research/publication/consistent-weighted-sampling/
https://arxiv.org/abs/1706.01172


It is a tool for generating Count-Min sketches and consistent weighted samples for varying sized data streams. The implementation has been tested over artificially generated datasets with size upto $10^8$. The library contains:
- implementations for distance measurements (Jaccard, Hamming, Euclidean, Edit, Manhattan, Cosine). 
- Count-Min Sketch tables. Adding stream elements to the table, and fast look-up.
- CWS with settings from original paper. CWS adaptation over Count-Min tables and iterable streams. Sketching CMS tables
- Artificial dataset generation tools, random number generation via uniform, gamma, beta random variables.

__Note:__ Please, install/use C++ 11 or higher. Boost should be installed for some features.



