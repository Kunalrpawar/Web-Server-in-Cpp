function showTime() {
    const timeDisplay = document.getElementById('time-display');
    const now = new Date();
    const timeString = now.toLocaleString();
    
    timeDisplay.innerHTML = `
        <strong>Current Server Time:</strong><br>
        ${timeString}<br>
        <small>Request processed at: ${now.toISOString()}</small>
    `;
}

// Auto-refresh admin panel every 5 seconds
if (window.location.pathname === '/admin') {
    setInterval(() => {
        location.reload();
    }, 5000);
}

// Add some interactive features
document.addEventListener('DOMContentLoaded', function() {
    // Add click effects to features
    const features = document.querySelectorAll('.feature');
    features.forEach(feature => {
        feature.addEventListener('click', function() {
            this.style.transform = 'scale(0.95)';
            setTimeout(() => {
                this.style.transform = '';
            }, 150);
        });
    });
    
    // Add typing effect to header
    const header = document.querySelector('header h1');
    if (header) {
        const text = header.textContent;
        header.textContent = '';
        let i = 0;
        const typeWriter = () => {
            if (i < text.length) {
                header.textContent += text.charAt(i);
                i++;
                setTimeout(typeWriter, 100);
            }
        };
        typeWriter();
    }
}); 