# Guardian Angel Protocol (GAP)

A hardware guard architecture for keeping powerful systems — including AI — behind cryptographic lock and key.

## What GAP is

GAP is a standalone silicon security architecture: a dedicated hardware guard that stands between a host system and the outside world and decides, in hardware, what is allowed to happen. Every command the host issues is treated as untrusted until the guard has authenticated it. The system being guarded has no path to reach, inspect, or influence the guard.

Modern AI is controlled by software policy. Software policy can be patched, prompted around, or lied to. GAP moves the enforcement into silicon, where the rules are the structure of the chip itself.

## What it does

- **Authenticates everything.** Every instruction is cryptographically verified before it is acted on. Unsigned, altered, or replayed commands are rejected.
- **Enforces in dedicated logic, not software.** A compromised host or model cannot argue, prompt, or exploit its way past a guard it cannot touch.
- **Contains faults autonomously.** An isolated fault is contained and the system recovers on its own, without human intervention.
- **Locks down under attack.** Unauthenticated access, tampering, or attack-pattern behavior drives the system into a hard lock.
- **Answers to a human.** A hard lock can only be cleared by human-held authorization. No software path clears it.
- **Stays locked.** Guard state is held in tamper-resistant storage across power cycles. Cutting power does not reset the guard's memory of an attack.

## Verification status

Stated exactly, as of 2026-10-20:

- **Functional verification:** complete integrated simulation of the full design — all checks passing.
- **Synthesis:** the whole design has been run through logic synthesis (Yosys) — 114,210 cells for the complete chip in a single run. Per-module fine mapping is in progress.
- **Not yet:** the design has not been placed and routed, and it has not been fabricated. GAP is a verified design on the road to silicon — not a finished chip, and not claimed as one.

## Fingerprint (SHA-512)

The complete specification and source — the GAP V1.2 RTL Handoff (Rev 1.2-R2), the spec resolutions, the trust boundaries, the verification status, and the complete Veracore v1 source — are held privately under the UPAL. The fingerprints below are published as a public, timestamped commitment to that exact body of work. When the bundle is revealed, these hashes will match it byte for byte.

```
VERACORE v1 — SHA-512 fingerprints — 2026-10-20
Bundle (393,611 bytes): ade43b029ce93823366b65bd75d5949627bcf86c2346397bdb9981fa0c8908b52fe4806d4f9d2ffaf5b430e9f5d455f3994b2953f6dbdbddd906654850431c60
- GAP V1.2 RTL Handoff Spec Rev 1.2-R2 (PDF): ac9b373a5607131ae44c8e998a5d3092e51d2b70c0ce9e5fd9f1a2a6c43ca83f112693745269da99844ec5c32573331956d42343206d781734b4b2c2b313874b
- SPEC_GAP_RESOLUTIONS.md: 8eb5ce0678cc05a888ac099fcbb2742d756e9dfebf9e3edb079730b5e376560b98c2157df25abe46465833cfa68b86fe932942b17f2febca36052fe3d6eaa276
- TRUST_BOUNDARIES.md: 90fdc9777e18f51947619020f1db2e9214ca6904e1c6358236a9371a0b23654365eee342f4abb40305e8cc9d748f68884fa3c720ad5e2420f53e43c345b51dfd
- VERIFICATION_STATUS.md: 15b4e94b0a9b50abc810c29c6726e9dadc02d6f8e86d8e049175c5055640c222efa4e6009693465f86fd16f7647c19e94171d6dfcee62e3e396cf6bce772a0da
- VERACORE_V1_COMPLETE_SOURCE.txt: fdb61650f89371bcafd2bdfc416017240176952a9ac6aad81ffac6775332151324a1d6dbd8aa6b405867c19f506b716b16c8c58c2c097250e427ef9c5df3cfe0
```

## License

GAP is proprietary architecture, offered under the Universal Proprietary Architecture License (UPAL) v5.2.0: personal, non-commercial research and evaluation only. Commercial use and use by entities require a separate license.

The GAP architecture is the subject of a pending U.S. patent application (No. 64/047,130, filed April 23, 2026). The Veracore v1 RTL implementation — the standalone-silicon realization of that architecture — will be covered by its own filing.

© Alexander Dylan Philip Colclough. All rights reserved.
