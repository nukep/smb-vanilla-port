# This script calls other scripts

def run_script(scriptname):
    # I can't for the life of me find a way to run a Python script in an isolated way
    # I don't want the state of the previous script to affect the next
    # So we save the global state, run the script, then restore the old state
    _globals_known = globals().copy()
    runScript(scriptname, state)
    g = globals()
    g.clear()
    g.update(_globals_known)

def run_all_scripts():
    import time
    run_script("smb2j_import.py")
    run_script("smb_init_memorymaps.py")
    run_script("smb2j_datatypes.py")
    run_script("smb2j_fixup_branches.py")
    run_script("smb2j_jumptables.py")
    run_script("smb2j_reset_and_nmi.py")
    run_script("smb2j_fixup_refs.py")
    run_script("smb_create_extra_fns.py")
    # # Absurdly, there seems to be a race condition in Ghidra that shows up in the next script.
    # # Ghidra creates CALL_RETURN flow overrides in the jumptable patches if we don't sleep here (???????)
    time.sleep(1)
    run_script("smb_fn_coverage.py")
    run_script("smb2j_remove_fallthru_overrides.py")
    # run_script("smb_flow.py")
    # run_script("smb_tag_fns_to_omit.py")

run_all_scripts()
