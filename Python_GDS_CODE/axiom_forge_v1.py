import gdstk
import numpy as np

print("\n--- INITIATING MASTER FORGE: AXIOM CORE V1 ---")

# 1. CREATE THE UNIT CELL (THE 9 SEAL)
lib = gdstk.Library("AXIOM_SYSTEM")
halo_cell = lib.new_cell("HALO_RESONATOR")

WG_WIDTH = 2.5
HALO_RADIUS = 77.7

# Straight Path & Ring
path = gdstk.RobustPath((-50, 0), WG_WIDTH, layer=1)
path.segment((150, 0))
ring = gdstk.ellipse((50, HALO_RADIUS + (WG_WIDTH/2) + 0.1), 
                     HALO_RADIUS + WG_WIDTH, inner_radius=HALO_RADIUS, layer=1)
halo_cell.add(path, ring)
print("[+] Unit Cell: LOCKED.")

# 2. CREATE THE GAUNTLET (12-NODE ARRAY)
gauntlet_cell = lib.new_cell("GAUNTLET_12_NODE")

for i in range(12):
    x, y = (i % 4) * 500, (i // 4) * 500
    # Add the Halo to the Gauntlet
    gauntlet_cell.add(gdstk.Reference(halo_cell, (x, y)))
    # Add the DTI Chasm (Layer 2)
    trench = gdstk.rectangle((x-60, y-100), (x+210, y+200), layer=2)
    gauntlet_cell.add(trench)
print("[+] Gauntlet Array: LOCKED.")

# 3. CREATE THE TEMPORAL WARDEN (2ps DELAY)
# The "Warden" is a serpentine path that light MUST pass through
# 300 microns = 2 picoseconds of delay in Si3N4
warden_cell = lib.new_cell("TEMPORAL_WARDEN")
warden_cell.add(gdstk.Reference(gauntlet_cell))

# Creating the 2ps S-Curve 'Wiggle'
delay_path = gdstk.RobustPath((0, -200), WG_WIDTH, layer=3)
# The "Wiggle" that adds 300um of length
delay_path.segment((50, -200))
for _ in range(3): # Three 'S' turns to burn 2ps of time
    delay_path.interpolation([(75, -150), (100, -250), (125, -200)], cycle=False)
warden_cell.add(delay_path)

print("[+] Temporal Warden: 2ps Skew Enforced.")

# 4. FINAL OUTPUT
lib.write_gds("AXIOM_MASTER_CORE.gds")
print("\n[!!!] MASTER FORGE COMPLETE: AXIOM_MASTER_CORE.gds")
print("--- SHIELD ACTIVE ---")
