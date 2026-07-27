# Phishing Awareness Analysis

## Why This Matters

Most breaches don't start with a genius hacker cracking encryption — they start with someone clicking a link they shouldn't have. Firewalls and antivirus software can't stop an employee from typing their password into a fake login page. That's why the first and most important line of defense in any organization is a trained human being who knows how to pause, question, and verify before acting.

This project analyzes three realistic phishing scenarios, identifies the specific red flags in each, and applies a simple decision framework anyone — technical or not — can use to respond correctly.

## The Framework: Pause → Verify → Report

Before looking at the examples, here's the rule everything below is built on:

1. **Pause** — Notice the emotional pull (urgency, fear, curiosity, authority) and stop before clicking, replying, or downloading anything.
2. **Verify** — Confirm the request through a separate, trusted channel. If an email claims to be from your manager, call them — don't reply to the email.
3. **Report** — Flag it through proper channels instead of just deleting it, so others don't fall for the same message.

---

## Scenario 1: The Fake IT Password Reset

**Message:**
> **From:** IT Security Team it-support@company-secure-portal.com
> **Subject:** URGENT: Your password expires in 2 hours — Action Required
>
> Dear Employee,
> Our system has flagged your account for a mandatory password reset. Failure to update within 2 hours will result in permanent account suspension. Click below to verify your identity and reset your password immediately.
>
> [Reset My Password Now]
>
> IT Security Team

**Red Flags Identified:**
- **Sender-domain mismatch** — "company-secure-portal.com" is not the real company domain, just designed to look official
- **Artificial urgency** — a 2-hour deadline with a scary consequence (account suspension) to short-circuit careful thinking
- **Generic greeting** — "Dear Employee" instead of an actual name, common in mass-sent phishing
- **Authority impersonation** — posing as "IT Security Team" to demand unquestioned compliance

**Classification: Malicious**
This has no legitimate business reason to threaten account suspension over email, the domain doesn't match the company's real one, and the urgency is manufactured to prevent the recipient from stopping to verify. This is a textbook credential-harvesting attempt.

**Action: Block & Escalate** — Report to the actual IT/security team and do not click the link.

---

## Scenario 2: The CEO Wire Transfer Request (Business Email Compromise)

**Message:**
> **From:** CEO Name (traveling) ceo.name@gmail.com
> **Subject:** Quick favor — confidential
>
> Hi, I'm in a meeting and can't talk right now, but I need you to process an urgent wire transfer before end of day. This is time-sensitive and confidential — please don't loop anyone else in for now. I'll send account details shortly. Can you confirm you're available?
>
> Thanks,
> [CEO Name]

**Red Flags Identified:**
- **Sender-domain mismatch** — a real CEO's business email wouldn't come from a personal Gmail address
- **Urgent bypass request** — explicitly asking to skip normal procedure ("don't loop anyone else in")
- **Authority + urgency combo** — using the CEO's position to demand quick, unquestioned action
- **Vague follow-up promise** — "I'll send details shortly" is a common tactic to get a commitment before the victim can think it through

**Classification: Malicious**
This is a classic Business Email Compromise (BEC) attempt. Legitimate executives don't request confidential financial actions over email from personal accounts, and any request to bypass standard procedure is an immediate red flag regardless of who appears to be asking.

**Action: Block & Escalate** — Verify directly with the CEO through a known phone number before taking any action, and report the email to security.

---

## Scenario 3: The QR Code "Account Recovery" Prompt

**Message (found as a poster/flyer near a shared workspace, also seen as a mobile pop-up):**
> **Google Account Recovery**
> Your account access will be locked in 24 hours due to unusual activity.
> Scan this QR code to verify your identity and restore access.
> [QR CODE IMAGE]

**Red Flags Identified:**
- **Quishing (QR phishing)** — designed to push the victim onto a mobile device, where it's harder to inspect a URL before tapping
- **Fake activity alert** — an alarming, vague "unusual activity" claim with no specifics
- **Bypasses normal URL inspection** — QR codes hide the destination link until it's already opened
- **Urgency trigger** — a 24-hour lockout threat to prevent careful verification

**Classification: Suspicious → escalates to Malicious upon scanning**
Even without scanning it, an unsolicited QR code demanding urgent "account verification" in a public or shared space is inherently suspicious — legitimate account security notices don't arrive this way.

**Action: Warn User** (before scanning) → escalates to **Block & Escalate** if scanned and a suspicious page loads. Never scan an unsolicited QR code claiming account urgency; report it to security or facilities if found on physical premises.

---

## Quick Triage Checklist

A fast, non-expert scan for any suspicious message — if any of these apply, treat it as Suspicious or Malicious rather than Safe:

- [ ] Sender's actual email address doesn't match the display name or company domain
- [ ] Message creates urgency, fear, or a tight deadline
- [ ] Asks you to bypass normal procedure or keep the request secret
- [ ] Requests passwords, MFA codes, or payment/account details directly
- [ ] Contains an unexpected attachment or unusual file type (.iso, .js, .scr)
- [ ] Includes a QR code you weren't expecting
- [ ] Login pop-up can't be dragged outside the browser window
- [ ] You're getting repeated MFA push notifications you didn't request
- [ ] The message only gives a phone number to call, no link — but pressures urgency
- [ ] Something just feels slightly "off" even if you can't immediately say why

**If two or more boxes are checked: Pause. Verify through a separate channel. Report it. Don't act on the message itself.**

## Conclusion

Phishing succeeds by exploiting human psychology, not technical vulnerabilities — urgency, authority, fear, and curiosity are the actual attack surface. The three scenarios above cover the most common real-world patterns: credential harvesting, executive impersonation, and modern QR-based attacks. The Pause–Verify–Report framework turns awareness into a repeatable habit, which is ultimately what separates a resilient organization from a vulnerable one.
