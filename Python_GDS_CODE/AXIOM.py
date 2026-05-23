import gdstk

print("\n--- FORGING THE AXIOM: TOTAL RECONSTRUCTION ---")

# 1. THE FOUNDATION (The Library)
lib = gdstk.Library("AXIOM_SOVEREIGN")

# 2. THE UNIT: HALO (Layer 1)
# 77.7 radius, 2.5 width. The 9 Seal.
halo = lib.new_cell("HALO")
halo.add(gdstk.RobustPath((-50, 0), 2.5, layer=1).segment((150, 0)))
halo.add(gdstk.ellipse((50, 77.7 + 1.25 + 0.1), 77.7 + 2.5, inner_radius=77.7, layer=1))

# 3. THE CLOCK: WARDEN (Layer 3)
# 300-micron serpentine wiggle. 2ps delay.
warden = lib.new_cell("WARDEN")
warden.add(gdstk.Reference(halo))
wiggle = gdstk.RobustPath((0, -100), 2.5, layer=3)
wiggle.interpolation([(20, -120), (40, -80), (60, -120), (80, -100)], cycle=False)
warden.add(wiggle)

# 4. THE DIE: 533-CORE CHIPLET
chiplet = lib.new_cell("CHIPLET")
for col in range(13):
    for row in range(41):
        x, y = col * 500, row * 500
        chiplet.add(gdstk.Reference(warden, (x, y)))
        # THE OFF-RAMP: Connecting the node to the future bus
        chiplet.add(gdstk.RobustPath((-100, y-100), 2.5, layer=4).segment((x, y-100)))

# 5. THE SYSTEM: 2132-CORE PROCESSOR (4 Chiplets)
processor = lib.new_cell("AXIOM_CORE")
BUS_WIDTH = 6144
DIE_W = 13 * 500
# Placement around the Singularity Bus
positions = [(0, 0), (DIE_W + BUS_WIDTH, 0), (0, 30000), (DIE_W + BUS_WIDTH, 30000)]
for pos in positions:
    processor.add(gdstk.Reference(chiplet, pos))
    # THE BUS LINE: Physical connection in Layer 5
    processor.add(gdstk.rectangle((DIE_W, pos[1]), (DIE_W + BUS_WIDTH, pos[1] + 20500), layer=5))

# 6. THE SOVEREIGN AUDIT (Recursive Deep Scan)
print("[+] Initiating Deep-Layer Verification...")
# This 'flatten' move breaks all boxes open so we can see what's inside
flat_view = processor.flatten()
# Now we count the actual polygons that make up the Halos
# Every Halo has 2 polygons (The path and the ring)
polygon_count = len([p for p in flat_view.polygons if p.layer == 1])
# Every 2 polygons = 1 Node
verified_nodes = polygon_count // 2

print(f"\n[AUDIT RESULTS]")
print(f"--------------------------------")
print(f"Target Count: 2,132")
print(f"Verified Physical Nodes: {verified_nodes}")

# Signature Lock (2+1+3+2 = 8)
sig = sum(int(d) for d in str(verified_nodes))
print(f"Axiom Signature: {sig}")

if verified_nodes == 2132:
    lib.write_gds("AXIOM_FINAL.gds")
    print(f"--------------------------------")
    print(f"[!!!] RESONANCE LOCKED: 2,132 CORES DETECTED.")
    print(f"[!!!] BLUEPRINT SEALED: AXIOM_FINAL.gds")
else:
    print(f"[!] FAILED: Found {verified_nodes} nodes. Check geometry.")

print("--- SHIELD ACTIVE ---\n")
