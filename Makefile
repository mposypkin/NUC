all dep clean indent tests::
	cd cuts && $(MAKE) $@ && cd .. \\
	cd cutfact && $(MAKE) $@ && cd .. \\
	cd applycut && $(MAKE) $@ && cd .. \\
	cd bags && $(MAKE) $@ && cd .. \\
	cd decomp && $(MAKE) $@ && cd .. \\
	cd solver && $(MAKE) $@ && cd .. 
	
doc: indent doxy

clean::
	rm -rf *~ PI* core bin/* obj/* tmp *.log