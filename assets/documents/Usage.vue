<template>
  <div>
    <strong>Usage:</strong>
    Select a file using one of the above pull-down menus, and check
    a radio button to select a checking property (CR, CR(CBV)
    or SN) for your choice. ▶ button for checking. You can
    also submit custom rewrite rules. Firstly [CLEAR], then fill the
    form with your rules written in one of the formats (SOL,or TRS).
    Finally, check a radio button for checking property, and push
    ▶ button.<br>
    <strong>Checking Confluence for GHC Rules:</strong>
    The rules are confluent if they are both locally confluent and
    terminating. Use the option WCR to check local confluence and
    the option SN to check termination.<br>
    The tool actually compiles the program, so any unmet dependency
    will result in a failure. In particular, the program may only
    import modules from the
    <a href="https://hackage.haskell.org/package/base">base package </a>.
    Also, the usual syntax rules for Haskell program applies: if 
    the program does not compile on a machine then checking will not 
    be possible. Please, make sure that the program compiles
    on your machine first. We tested the tool with GHC version 8.8.2.
  </div>
</template>
