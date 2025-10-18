# Final Project Minimum Requirements

## Overview
This document outlines the minimum scope requirements for the final project submission. Projects must meet all specified criteria to ensure adequate complexity and demonstration of key concepts.

## Submission Requirements
- **Gameplay Video/GIF**: 30-60 seconds demonstrating the project in action

---

## Core Requirements

### 1. Randomness Requirement
Projects must incorporate randomness to ensure variability between runs.

#### Examples for Maze Projects:
- Random maze generation each run, OR
- Random starting position/orientation for robot, OR
- Random goal location within valid maze position

#### Examples for Block Sweeping Projects:
- Random initial block placement (minimum 20 blocks), OR
- Random block spawning at intervals (size, position, timing), OR
- Random starting positions/orientations for robots

### 2. Game Mechanics Requirement

#### Required Elements:
- **Visual Feedback**: Score/timer displayed on screen
- **Clear End State**: Game must have definite win/loss/completion with on-screen notification when finished
- **Restart Capability**: Ability to run multiple rounds via button click

#### Example Block Sweeping Project Specific Requirements:
- **Goal**: Score more points than opponent robot
- **Scoring Examples**:
  - +1 point per block deposited in your zone
  - Bonus points for larger blocks
- **Win Condition**: Highest score after fixed time period (e.g., 2 minutes)
- **Display Requirements**: Score counter for each robot and timer

### 3. Environmental Requirement
The game environment must include:
- **Static obstacles**
- **Dynamic elements** (moving blocks, spawning items, etc.)
- **Boundaries** with proper collision handling

### 4. Clear "Win" or "End" Condition
There must be a specific, measurable goal. Examples include:
- Collecting a certain number of items
- Reaching a designated area
- Surviving for a set amount of time against hazards
- Tagging or "capturing" another autonomous agent

### 5. Sensor Integration
The robot must use **at least one type of sensor** to gather information from the environment.

---