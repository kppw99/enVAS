long CVE_2011_1182_PATCHED_do_rt_tgsigqueueinfo(pid_t tgid, pid_t pid, int sig, siginfo_t *info)
{
	/* This is only valid for single tasks */
	if (pid <= 0 || tgid <= 0)
		return -EINVAL;

	/* Not even root can pretend to send signals from the kernel.
	 * Nor can they impersonate a kill()/tgkill(), which adds source info.
	 */
	if (info->si_code != SI_QUEUE) {
		/* We used to allow any < 0 si_code */
		WARN_ON_ONCE(info->si_code < 0);
		return -EPERM;
	}
	info->si_signo = sig;

	return do_send_specific(tgid, pid, sig, info);
}
