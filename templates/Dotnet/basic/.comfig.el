;; .comfig.el

(setq compilation-auto-jump-to-first-error t)

(defun call/MakeFile-test ()
  (interactive)
  (if-let ((project-root (projectile-project-root)))
      (let ((default-directory project-root))
        (compile "dotnet run"))
    (message "Not in a Projectile project.")))

(global-set-key (kbd "C-c m t") #'call/MakeFile-test)
