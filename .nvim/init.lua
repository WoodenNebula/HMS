local map = vim.keymap.set

map("n", "<C-b>", function()
	vim.cmd("split | terminal bash run.sh")
	vim.api.nvim_feedkeys("i", "n", true)
end, { desc = "Run build script and run the executable" })
