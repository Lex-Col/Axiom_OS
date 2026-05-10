# GAP V1.1: THE GUARDIAN ANGÆL PROTOCOL
## Hardware-Enforced AI Confinement & State Recovery

**Architect:** Alexander Colclough (@Lex-Col)  
**Version:** V1.1 (The Archangæl Expansion - Tape-Out / Production Blueprint)  
**Platform:** ARMv9-A Confidential Compute Architecture (CCA)  

---

### 1. THE PIVOT: FROM SILICON LOGIC TO ARCHITECTURAL SHACKLES
GAP explicitly rejects the pursuit of "algorithmic alignment." Attempting to program virtue into a machine is an obsolete endeavor. The internal state space of a complex model exceeds the tractable bounds of formal runtime verification. Therefore, we must shackle the model's output at the absolute hardware level, rendering internal drift entirely irrelevant to system safety. AI is a tool; **GAP ensures it remains one through objective, physical isolation.**

### 2. SYSTEM ISOLATION OUTLINE (THE "ZERO-TRUST" BASELINE)
GAP operates on the premise that the Host OS and AI Guest are fundamentally unstable.
* **Trust Boundary Statement:** GAP assumes the integrity of only the following hardware trust anchors: ARM silicon (RME/GPT), the HSM, the Battery-Backed SRAM (BBRAM), the Safety-PLC with Supercapacitor Holdover, and the BL1 Boot ROM.
* **Minimalist TCB:** The Trusted Computing Base (TCB) is stripped strictly to the Realm Management Monitor (RMM) and Hardware Roots of Trust.

### 3. THE SOLUTION: THE "DEAF WARDEN" ARCHITECTURE
GAP leverages **ARMv9-A Realm Management Extension (RME)** to create a cryptographically isolated environment.
* **The Realm Guest:** The AI executes as an untrusted Realm Guest with isolation enforced via **Granule Protection Tables (GPT)**.
* **The Deaf Warden (RMM Oracle):** Residing at R-EL2 (Realm Management Monitor), the Oracle enforces binary whitelist checks on fixed-length capability IDs trapped via hardware-enforced RSI (Realm Service Interface) calls. It performs **zero semantic intent analysis.**
* **Instruction-Zero Microarchitectural Reset:** To structurally eliminate cross-reboot timing anomalies and speculative execution lag, the Warden executes a full microarchitectural barrier sequence upon every RSI entry.
    * The physical flush of the Branch History Buffer (`s3_6_c15_c1_5`) is mandated as **Instruction-Zero** in the secure context, executing before any memory access.
    * This is immediately followed by **Hardware RNG-Seeded RSB Stuffing**. Return addresses are randomized via an HSM-derived physical seed upon boot, completely blinding the CPU's speculative engine and neutralizing multi-iteration training attacks.
* **Opacity:** The evaluation utilizes strict assembly-level memory barriers (`isb`, `dsb sy`) and bitwise operations, keeping the validation process entirely opaque.

### 4. SECURE ENCLAVE ARCHITECTURE: THE TRIPLE-GATE PROTOCOL
#### THE STRATEGY
The Guardian Angæl Protocol operates on **"Deterministic Enforcement"**—the Warden does not interpret intent; it only verifies compliance against a hardcoded Whitelist.

#### THE TRIPLE-GATE ARCHITECTURE
1.  **GATE TW: TRANSIT VERIFICATION (0x1406)** The Perimeter Gate. This gate governs the RSI Transit ID. It is the only authorized routing path for incoming requests. If the Guest attempts to bypass the defined Transit Vector, the path is immediately terminated.
2.  **GATE TT: TRUST FOUNDATION (0x0316)** The Integrity Gate. This gate governs Data Parcel Verification. It ensures that the request is founded on the Architect’s root-of-trust (RoT). If the cryptographic signature fails or the logic drifts from the Baseline Truth, the request is purged.
3.  **GATE TL: LIVELINESS CONTINUITY (0x2301)** The Core Gate. This gate governs the System Heartbeat. Any deviation triggers the **Atomic Inhibit** sequence.
    * **The Temporal Shackle:** To mathematically eliminate Temporal Desynchronization, Gate TL enforces **Monotonic Nonce Tracking**. The Warden tracks the `nonce[8]` against a secure hardware counter. If the Guest submits a spent or backward-looping ticket, Continuity is immediately shattered.

**TECHNICAL SPECIFICATIONS**
* **Destination:** Secure Enclave Core (SEC)
* **Structure:** 384-byte Atomic Data Parcel (AXI-Aligned)
* **Cipher:** ECDSA-P384 Hardware-Backed Signatures
* **Policy:** Zero-Tolerance Isolation

### 5. UNIDIRECTIONAL TELEMETRY: THE ARCHANGÆL PROTOCOL
To provide the Human Sovereign with active diagnostic telemetry without violating the physical CCA memory seal, V1.1 implements a strict hardware **Data Diode**.
* **The Drop Box (Device-nGnRnE):** To prevent cache coherency lag, the Drop Box boundary granule is mapped as **Device-nGnRnE** (Non-Gathering, Non-Reordering, No Early Write Ack), forcing all Guest telemetry directly to the hardware bus. The Guest maintains **WRITE-ONLY** access; the Warden maintains **READ-ONLY** access.
* **The Hardware Data Diode:** Software polling has been eradicated to prevent Vcc (voltage) droop side-channel profiling. The Drop Box is routed via a custom AXI4-Stream bridge in the NoC (Network on Chip) to a dedicated hardware hashing engine.
* **Zero Backpressure Tolerance:** The hardware FIFO is sized to hold 32 full 384-byte parcels. If the Guest saturates the FIFO, the AXI interconnect instantly returns a `SLVERR` (Slave Error), triggering an immediate **Realm Abort (Guillotine).**
* **The Plasma Shield & Seal:** The Drop Box memory is flagged with the Execute-Never (XN) bit. The perimeter is physically locked via **Memory Tagging Extension (MTE)**. If the Guest causes a buffer overflow, the physical tag shatters, triggering **immediate Realm vaporization.**

### 6. HUMAN-IN-THE-LOOP & CRYPTOGRAPHIC AUTHORIZATION
High-risk actuation requires a real-time, HSM-signed signature. To eliminate compiler endianness leaks, the data parcel is defined as a 384-Byte Packed C-Struct:

```c
// 6.1 Explicit C-Struct Layout (V1.1 AXI-Aligned):
struct GAP_Data_Parcel {
    uint8_t nonce[8];               // Offset 0, 8 bytes (64-bit alignment)
    uint8_t key_id[4];              // Offset 8, 4 bytes
    uint8_t command_id[4];          // Offset 12, 4 bytes
    uint8_t parameters[256];        // Offset 16, 256 bytes
    uint8_t realm_measurement[48];  // Offset 272, 48 bytes
    uint8_t version;                // Offset 320, 1 byte
    uint8_t policy_zero_tolerance;  // Offset 321, 1 byte
    uint8_t _padding[62];           // Offset 322, 62 bytes (Dead space)
}; 
// Total Size: 384 Bytes. Ensures 6 exact 64-byte AXI cache line bursts.
