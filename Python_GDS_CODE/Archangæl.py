import gdstk

print("\n--- GENERATING ARCHITECT'S MACRO VIEW ---")

# 1. Load the locked spec file
lib = gdstk.read_gds("AXIOM_2132_SPEC_LOCKED.gds")
# 2. Grab the top-level processor
top_cell = lib.top_level()[0]

# 3. Write a high-detail SVG of the core interaction zone
# We're limiting the view to the first 4 nodes to keep it clean
top_cell.write_svg("AXIOM_MACRO_VIEW.svg", 
                   scaling=10, 
                   pad="5%", 
                   precision=0.01)

print("[+] Macro View Generated: AXIOM_MACRO_VIEW.svg")
print("[+] Move this to your Downloads folder to view.")
s
