SUBDIRS := Observer

.PHONY: all clean $(SUBDIRS)

all: $(SUBDIRS)

$(SUBDIRS):
	@if [ -d $@ ]; then \
		$(MAKE) -C $@; \
	else \
		echo "Skipping $@ - Directory not found"; \
	fi

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done