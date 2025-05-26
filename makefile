# === Configuration ===
BIN_NAME       := template
SRC_DIR        := src
SRC_FILES      := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES      := $(SRC_FILES:.c=.o)
INSTALL_BIN    := /usr/local/bin/$(BIN_NAME)
TEMPLATE_SRC   := templates
TEMPLATE_DEST  := /usr/share/templates

CC             := gcc
CFLAGS         := -Wall -Wextra -O2

# === Targets ===

.PHONY: all clean install install-templates uninstall

all: $(BIN_NAME)

$(BIN_NAME): $(OBJ_FILES)
	$(CC) $(CFLAGS) -o $@ $^

# Object files need to be placed in same folder as sources
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(BIN_NAME) $(OBJ_FILES)

install: $(BIN_NAME)
	@echo "🔧 Installing binary to $(INSTALL_BIN)..."
	sudo install -m 755 $(BIN_NAME) $(INSTALL_BIN)
	@echo "✅ Done."

install-templates:
	@if [ ! -d "$(TEMPLATE_SRC)" ]; then \
		echo "❌ No templates found in $(TEMPLATE_SRC)"; \
		exit 1; \
	fi
	@echo "📦 Installing templates to $(TEMPLATE_DEST)..."
	sudo mkdir -p "$(TEMPLATE_DEST)"
	sudo rsync -a --checksum --update --delete "$(TEMPLATE_SRC)/" "$(TEMPLATE_DEST)/"
	@echo "✅ Templates updated."

uninstall:
	@echo "🧹 Removing binary from $(INSTALL_BIN)..."
	sudo rm -f $(INSTALL_BIN)
	@echo "🧼 Removing templates from $(TEMPLATE_DEST)..."
	sudo rm -rf $(TEMPLATE_DEST)
	@echo "✅ Uninstall complete."
