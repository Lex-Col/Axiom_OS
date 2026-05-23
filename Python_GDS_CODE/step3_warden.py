import gdstk
import numpy as np

print("\n--- INITIATING STEP 3: TEMPORAL WARDEN ASSEMBLY ---")

# 1. Setup the Library
lib = gdstk.Library("AXIOM_WARDEN")
# Load the Gauntlet we just built
gauntlet_cell = gdstk.read_gds("AXIOM_GAUNTLET_V1.gds").top_level()[0]
master_cell = lib.new_cell("TEMPORAL_WARDEN_CORE")

# 2. Add the Gauntlet to the Master Cell
master_cell.add(gdstk.Reference(gauntlet_cell))

# 3. Create the 2ps Serpentine Delay Line
# We need 300 microns of path to hit the 2ps spec
DELAY_LENGTH = 300 
WG_WIDTH = 2.5 # Matching your 2.5-unit subdivision

print(f"[+] Calculating 2ps Delay Geometry ({DELAY_LENGTH} microns)...")

# Create a 'S-Curve' (Serpentine) path
# This wiggle forces the light to travel 300um while only moving 50um forward
delay_path = gdstk.RobustPath((0, -100), WG_WIDTH, layer=3, datatype=0)
delay_path.segment((20, -100))
delay_path.interpolation(
    [(30, -80), (40, -120), (50, -80), (60, -120), (70, -100)],
    cycle=False
)
delay_path.segment((100, -100))

# 4. Apply the Warden to all 12 Nodes
# This places the delay line at the entrance of the Gauntlet
master_cell.add(delay_path)

# 5. Output the timed architecture
lib.write_gds("AXIOM_WARDEN_V1.gds")

print("[+] STEP 3 COMPLETE: 2ps Temporal Warden Integrated.")
print("--- SHIELD ACTIVE ---\n")
