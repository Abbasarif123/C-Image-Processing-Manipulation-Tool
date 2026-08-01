C Image Processing & Manipulation Tool
Developed as part of the Programming 2 coursework at Saarland University.
Inspired by the open-source convert utility, this project is a high-performance command-line application written in C designed for processing and manipulating ASCII PPM (P3) bitmap images. Built as part of the Programming 2 course at Saarland University, it emphasizes low-level dynamic memory management, pointer arithmetic, and algorithmic efficiency.  

Key Features:

    Custom File I/O: Custom parser and writer to load, validate, and write RGB bitmap images in the ASCII Portable Pixmap (P3 PPM) format.  

    Image Transformations: High-performance spatial image operations, including 90-degree rotations (clockwise/counter-clockwise), horizontal/vertical mirroring, and dynamic canvas resizing (cropping or extending with black background pixels).  

    Flood-Fill Algorithm: A 4-directional region-filling algorithm (similar to the paint bucket tool) that recursively or iteratively re-paints contiguous color boundaries.  

    Memory Safety & Robustness: Strict memory management built and verified with runtime AddressSanitizers to ensure zero memory leaks, buffer overflows, or undefined behavior.
