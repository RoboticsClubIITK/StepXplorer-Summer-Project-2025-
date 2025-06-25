# StepXplorer-Summer-Project-2025-
StepXplorer is a stair-climbing robot developed as part of the Robotics Club, IIT Kanpur’s Summer Projects, aimed at enabling wheeled robots to traverse vertical steps through an innovative mechanical design.

Unlike traditional legged robots, StepXplorer employs a gear-driven, rotating wheel mechanism that allows it to climb stairs with controlled motion and stability. The project addresses the challenge of navigating human-designed environments using a compact, Arduino-controlled platform with minimal electronics.

The initiative emphasized hands-on learning in mechanical design, control systems, and embedded programming. Through iterative prototyping, the team explored various climbing mechanisms and refined motor control algorithms for reliable performance.

A secondary goal was to implement a self-balancing platform that keeps the payload surface level using servo-driven stabilization. This repository documents the project's motivation, design approach, control logic, challenges, and final outcomes.



 ## 📚 Phase 1: Training & Knowledge Building

The initial three weeks were focused on introducing club members and interns to essential robotics concepts, including:
- Arduino programming and serial communication
- Sensor integration (Ultrasonic, IR, IMU)
- Motor driver interfacing
- Basic PID control principles
- Mini-projects for hands-on familiarity

This learning phase prepared the team for the collaborative development of StepXplorer.

## 🔧 Phase 2: Bot Design & Implementation

In the remaining 3 weeks, efforts were concentrated on:
- Designing a mechanically robust stair-climbing mechanism
- Constructing and assembling the gear train
- Implementing PID-based motor control using Arduino
- Testing climbing performance on various stair dimensions
- Adding a servo-based payload stabilization system

## 📁 Repository Structure

```bash
StepXplorer/
├── firmware/        # Arduino code for sensor reading, motor control
├── hardware/        # Circuit diagrams, wiring details
├── CAD/             # 3D design files for mechanical components
├── docs/            # Project report, images, design process
├── videos/          # Demo videos
├── LICENSE
└── README.md
