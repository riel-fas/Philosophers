<p align="center"> 
<img src="https://img.shields.io/badge/-000000?style=for-the-badge&logo=42&logoColor=white)](https://42.fr))"> 
<img src="https://img.shields.io/badge/1337-000000?style=for-the-badge&logo=1337&logoColor=white)](https://1337.ma))">  
<img src="https://img.shields.io/badge/Language-C-blue?style=for-the-badge&logo=c)">
</p> 
<h1 align="center">🧵 Philosophers 🧵</h1> 


# 🍽️ Philosophers - Threading & Synchronization Project

*Threading, Synchronization & The Dining Philosophers Problem*

---

## 🎯 Project Overview

The **Philosophers** project is a profound exploration of concurrent programming and synchronization in the 42 School curriculum. Based on Edsger Dijkstra's famous "Dining Philosophers Problem," this project challenges students to simulate philosophers sitting around a table, alternating between eating, thinking, and sleeping while sharing limited resources (forks).

> **Core Challenge:** Prevent deadlock and starvation while ensuring all philosophers can eat without conflicts, using proper thread synchronization techniques.

### The Dining Philosophers Problem Visualization

```
                    🧔 Philosopher 1
                         🍴
           🍴                      🍴
      🧔 P5        🔴 TABLE 🔴         🧔 P2
           🍴                      🍴
                🧔 P4    🍴    🧔 P3
```

**The Setup:**
- 5 philosophers sit around a circular table
- Each philosopher has a fork to their left and right
- To eat, a philosopher needs **both** adjacent forks
- After eating, they sleep, then think, then repeat the cycle

---

## ⚙️ Technical Specifications

### Core Requirements
- **Language:** C
- **Threading:** POSIX threads (pthreads)
- **Synchronization:** Mutexes and semaphores
- **Memory Management:** No memory leaks allowed
- **Timing:** Precise millisecond timing control

### Program Arguments
```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: times_each_philosopher_must_eat]
```

### Philosopher States & Their Transitions

```
🤔 THINKING → 🍽️ EATING → 😴 SLEEPING → 🤔 THINKING
     ↓              ↓           ↓           ↓
Time passes → Gets both forks → Releases → Back to
 normally      & eats food       forks     thinking

                    ↓ (if time_to_die exceeded)
                   💀 DEAD
```

**State Details:**
- **🤔 THINKING:** Philosopher contemplates life, not using any resources
- **🍽️ EATING:** Requires both adjacent forks, resets death timer
- **😴 SLEEPING:** Resting after eating, forks are released  
- **💀 DEAD:** Time since last meal exceeded `time_to_die`

---

## 🔐 Synchronization Challenges

### The Deadlock Problem

#### ❌ Deadlock Scenario:
```
P1 grabs Fork1    P2 grabs Fork2    P3 grabs Fork3
P1 waits Fork2    P2 waits Fork3    P3 waits Fork4
P4 grabs Fork4    P5 grabs Fork5
P4 waits Fork5    P5 waits Fork1

→ CIRCULAR WAIT = DEADLOCK! 🔄💀
```

#### ✅ Common Solutions:
1. **Resource Ordering:** Always acquire forks in numerical order
2. **Asymmetric Approach:** Odd philosophers grab left first, even grab right first
3. **Timeout Mechanism:** Release forks if waiting too long
4. **Semaphore Limiting:** Allow maximum N-1 philosophers to eat simultaneously

### Mutex Protection Strategy

```c
🔒 mutex_fork[0]  🔒 mutex_fork[1]  🔒 mutex_fork[2]  🔒 mutex_fork[3]  🔒 mutex_fork[4]
       ↑                ↑                ↑                ↑                ↑
   protects           protects        protects         protects         protects
    Fork 0             Fork 1          Fork 2           Fork 3           Fork 4
```

### Critical Synchronization Points:
- **🍴 Fork Access:** Each fork protected by individual mutex
- **🕐 Death Checking:** Shared timestamp requires protection
- **📝 Output Logging:** Printf statements need synchronization
- **🔢 Meal Counting:** Tracking eaten meals per philosopher

---

## 🗺️ Development Roadmap

### Phase 1: Foundation & Setup
**🎯 Objective:** Establish basic project structure and argument parsing

**Key Tasks:**
- Input validation and comprehensive error handling
- Data structure design for philosophers and simulation state
- Basic Makefile with proper compilation flags
- Understanding pthread fundamentals and linking

**Learning Focus:**
- Command-line argument parsing
- Memory allocation patterns for threaded programs
- Project organization for concurrent applications

---

### Phase 2: Threading Implementation  
**🎯 Objective:** Create and manage philosopher threads

**Key Tasks:**
- Thread creation with `pthread_create` for each philosopher
- Implement basic philosopher routine (eat-sleep-think loop)
- Thread attribute configuration and stack management
- Proper thread cleanup with `pthread_join`

**Learning Focus:**
- Thread lifecycle management
- Function pointer usage for thread routines
- Thread-specific data handling

---

### Phase 3: Mutex & Synchronization
**🎯 Objective:** Implement fork protection and resource sharing

**Key Tasks:**
- Mutex initialization for each fork using `pthread_mutex_init`
- Critical section identification and protection
- Deadlock prevention strategy implementation
- Atomic operations for shared data access

**Learning Focus:**
- Mutex operations (lock/unlock/trylock)
- Critical section design
- Resource acquisition ordering
- Lock-free programming concepts

---

### Phase 4: Timing & Death Detection
**🎯 Objective:** Implement precise timing and death monitoring

**Key Tasks:**
- Microsecond timing implementation with `gettimeofday`
- Death checker thread or monitoring system
- Last meal timestamp tracking per philosopher
- Simulation termination condition handling

**Learning Focus:**
- High-precision timing in C
- Time difference calculations
- Monitoring thread patterns
- Event-driven programming

---

### Phase 5: Output & Logging System
**🎯 Objective:** Implement thread-safe output and state reporting

**Key Tasks:**
- Protected printf statements with output mutex
- Timestamp generation for each log entry
- State change logging with proper formatting
- Clean simulation termination and final reporting

**Learning Focus:**
- Thread-safe I/O operations
- Formatted output in concurrent programs
- Logging best practices
- Clean shutdown procedures

---

### Phase 6: Optimization & Testing
**🎯 Objective:** Fine-tune performance and ensure reliability

**Key Tasks:**
- Memory leak detection using valgrind and manual checking
- Edge case testing (1 philosopher, 200+ philosophers)
- Performance optimization and bottleneck identification
- Stress testing with various timing parameters

**Learning Focus:**
- Debugging concurrent programs
- Performance profiling techniques
- Memory management in threaded applications
- Testing methodologies for concurrent code

---

## 🧠 Key Concepts & Learning Outcomes

### Threading Fundamentals
- **Thread Creation:** `pthread_create`, thread attributes, stack management
- **Thread Synchronization:** `pthread_join`, detached vs joinable threads
- **Shared Memory:** Global variables, data races, memory consistency
- **Thread Safety:** Atomic operations, volatile keyword, memory barriers

### Synchronization Primitives  
- **Mutexes:** `pthread_mutex_lock/unlock`, initialization, destruction
- **Deadlock Prevention:** Resource ordering, timeout mechanisms, detection algorithms
- **Starvation Avoidance:** Fair scheduling, priority inheritance
- **Critical Sections:** Minimal locking scope, lock granularity decisions

### System Programming
- **Precise Timing:** `gettimeofday`, `usleep`, microsecond-level control
- **Memory Management:** Dynamic allocation in multithreaded contexts
- **Error Handling:** Thread-safe error reporting, errno handling
- **System Calls:** Understanding kernel interactions and context switching

### Advanced Concepts
- **Lock-Free Programming:** Compare-and-swap operations
- **Producer-Consumer Patterns:** Resource sharing strategies  
- **Thread Pool Design:** Efficient thread management
- **Concurrent Data Structures:** Thread-safe implementations

---

## ⚠️ Common Pitfalls & Solutions

### 🚫 Data Races
**Problem:** Multiple threads accessing shared variables without synchronization
```c
// WRONG - Race condition
philosopher->last_meal = get_current_time();

// CORRECT - Protected access  
pthread_mutex_lock(&time_mutex);
philosopher->last_meal = get_current_time();
pthread_mutex_unlock(&time_mutex);
```

### 💀 Deadlock Scenarios
**Problem:** Circular wait for resources
**Solutions:**
- **Resource Ordering:** Always acquire mutexes in same order
- **Timeout Locks:** Use `pthread_mutex_timedlock`
- **Asymmetric Strategy:** Different acquisition patterns for odd/even philosophers

### ⏰ Timing Precision Issues
**Problem:** Inaccurate death detection due to timing granularity
**Solutions:**
- Check death condition frequently (every 1ms)
- Use high-precision timestamps
- Account for system scheduling delays

### 🧵 Thread Management Problems
**Problem:** Unjoined threads, resource leaks, zombie threads
**Solutions:**
- Always `pthread_join` created threads
- Proper cleanup in signal handlers
- Use `pthread_detach` only when appropriate

---
