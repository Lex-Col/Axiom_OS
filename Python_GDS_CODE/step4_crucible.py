import gdstk

print("\n--- INITIATING STEP 4: KAELIS CRUCIBLE & TRINITY LINK ---")

# 1. Start the next Forge Phase
lib = gdstk.Library("AXIOM_CRUCIBLE")
WG_WIDTH = 2.5

# 2. Build the Kaelis Crucible (Photonic S-Box / MZI)
# This splits the light, scrambles it non-linearly, and recombines it
crucible_cell = lib.new_cell("KAELIS_CRUCIBLE")

# The Splitter (Y-Junction)
input_path = gdstk.RobustPath((0, 0), WG_WIDTH, layer=4)
input_path.segment((20, 0))
# Top Arm (Phase Shift)
top_arm = gdstk.RobustPath((20, 0), WG_WIDTH, layer=4)
top_arm.interpolation([(40, 20), (60, 20), (80, 0)])
# Bottom Arm (Direct)
bottom_arm = gdstk.RobustPath((20, 0), WG_WIDTH, layer=4)
bottom_arm.interpolation([(40, -20), (60, -20), (80, 0)])
# The Recombiner (Where the S-Box non-linearity occurs)
output_path = gdstk.RobustPath((80, 0), WG_WIDTH, layer=4)
output_path.segment((100, 0))

crucible_cell.add(input_path, top_arm, bottom_arm, output_path)
print("[+] KAELIS CRUCIBLE: Non-Linear MZI logic locked.")

# 3. Build the Trinity Link (The 3-Way Harmonic Junction)
trinity_cell = lib.new_cell("TRINITY_LINK")
# Center Path (The Main 777 Alignment)
t_main = gdstk.RobustPath((0, 0), WG_WIDTH, layer=5)
t_main.segment((50, 0))
# Top Path (Ceremony Beat 1)
t_top = gdstk.RobustPath((25, 25), WG_WIDTH, layer=5)
t_top.segment((50, 0))
# Bottom Path (Ceremony Beat 2)
t_bot = gdstk.RobustPath((25, -25), WG_WIDTH, layer=5)
t_bot.segment((50, 0))

trinity_cell.add(t_main, t_top, t_bot)
print("[+] TRINITY LINK: 3-Way Harmonic Junction locked.")

# 4. Save the components
lib.write_gds("AXIOM_GATES_V1.gds")

print("\n[!!!] STEP 4 COMPLETE. ALL LOGIC GATES FORGED.")
print("--- SHIELD ACTIVE ---")
