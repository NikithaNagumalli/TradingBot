PROJECT_DIR=$(shell realpath .)
RUN_SCRIPT=$(PROJECT_DIR)/run.sh
init:
	@echo "[INFO] Creating symlink from $(RUN_SCRIPT) to ~/bin"
	@echo mkdir -p ~/bin
	@ln -s $(RUN_SCRIPT) ~/bin/run  # Replace with actual paths

build_app:
	@echo "[INFO] Building Trade Bot Application"
	@if [[ "$(KIND)" == "hard" ]]; then echo "[INFO] Deleting build directory"; rm -rf build; fi
	@./build.sh
