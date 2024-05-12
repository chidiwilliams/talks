---
theme: default
highlighter: shiki
lineNumbers: false
info:
drawings:
  persist: false
mdc: true
author: Chidi Williams
download: true
exportFilename: "Database Internals: Failure Detection"
keywords:
colorSchema: "light"
fonts:
  sans: IBM Plex Sans
---

# Failure Detection

## Database Internals, Chapter 9

<div class="absolute bottom-10">
  <span class="font-400 text-neutral-500">
    <span class="text-[#066e2e] font-600">SysDsgn</span> / 2024-05-12 / Chidi Williams
  </span>
</div>

---

# About Me

Chidi Williams

- Ex-Software Engineer at Goldman Sachs
- Co-Lead, SysDsgn
- [chidiwilliams.com](https://chidiwilliams.com)

---

# Failure Detection

- System failures need to be detected quickly
- Delays can increase latencies and reduce availability
- Differentiating between slow (unresponsive/faulty) and failed (dead/crashed) processes is difficult
  - Trade-off between:
    - Marking slow but alive processes as failed (false positives)
    - Not marking failed processes quickly enough (false negatives)
- Failures may be inter-process (_link_-level) or intra-process (_process_-level)

---

# Guarantees of Failure Detector Subsystems

- **Liveness**: Ensures intended events occur
- **Safety**: Prevents unintended events
- **Completeness**: All nonfaulty members detect failures
- **Efficiency vs Accuracy**: How fast the detector can identify process failures vs how accurately it can do so
  - _It's impossible to be both perfectly efficient and accurate_

---

# Heartbeats and Pings

- **Ping**: Query a process to expect a response in a given time
- **Heartbeat**: Process actively sends signals to indicate liveness
- Delayed responses can cause false positives
- Many failure-detection algorithms use heartbeats and timeouts, e.g. Akka's deadline failure detector

---

# Timeout-Free Failure Detection

- **Heartbeat Algorithm**: Uses counters instead of timeouts.
- **Assumptions**: Fair links, known network members.
- Each process sends heartbeat messages to all other processes; each message contains the path that the heartbeat has traveled so far. When a process receives a heartbeat, it increments counters for participants in the path, and sends the heartbeat to the ones not in the path. Processes stop propagating messages as soon as all known processes have been reached.
- **Pros**: Possible to detect a process is alive even if direct link to the process is faulty.
- **Downside**: Setting accurate thresholds for the counters is challenging.

---

# Outsourced Heartbeats

- Using neighbouring nodes to check for process liveness
- Processes only need to be aware of a subset of connected peers, not the entire network

---

# Phi-Accrual Failure Detector

- Probability-based failure detection
- Instead of binary (alive/dead) states, calculate probability of failure using approximate time arrival time of next heartbeat vs actual arrival time
- This method dynamically adjusts based on network conditions

---

# Gossip and Failure Detection

- Each process maintains a list of the states of neighbouring processes and shares this list with other members
- Allows information of failure to spread more reliably

---

# Reversing Failure Detection Problem

- **FUSE**: Group failure notification
- **Group Detection**: Failure detected in network partitions
- **Propagation**: Failure cascades through absence of responses

---

# Summary

- Failure detectors handle consensus problems in distributed systems
- Different strategies balance accuracy, precision, and simplicity
- Choose the approach that aligns best with system requirements

---

# Further Reading

- Chandra & Toueg (1996): "Unreliable Failure Detectors"
- Freiling et al. (2011): "The Failure Detector Abstraction"
- Phan-Ba (2015): "A Literature Review of Failure Detection"
