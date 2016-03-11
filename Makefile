all dep clean indent tests::
	cd cuts && $(MAKE) $@ && cd .. 

doc: indent doxy

clean::
	rm -rf *~ PI* core bin/* obj/* tmp *.log