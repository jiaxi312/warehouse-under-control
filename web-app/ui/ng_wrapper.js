#!/usr/bin/env node
const fs = require('fs');
const path = require('path');
const { execSync } = require('child_process');

console.log('CWD:', process.cwd());
console.log('__dirname:', __dirname);
try {
    console.log('./ list:', fs.readdirSync('.'));
    if (fs.existsSync('node_modules')) {
        console.log('./node_modules list:', fs.readdirSync('node_modules'));
        if (fs.existsSync('node_modules/@angular')) {
            console.log('./node_modules/@angular list:', fs.readdirSync('node_modules/@angular'));
        }
    } else {
        console.log('node_modules does not exist in CWD');
    }
} catch (e) {
    console.log('Error listing:', e.message);
}
console.log('Attempting to run ng build...');

try {
    // Try to resolve to check environment
    require.resolve('@angular-devkit/build-angular');
    require('@angular/cli/bin/ng.js');
} catch (e) {
    console.error('Angular CLI build failed or dependency missing:', e.message);
    console.log('Falling back to creating dummy dist for Bazel build...');

    // Ensure dist directory exists
    // We assume we are in web-app/ui (chdir)
    // But wait, if chdir is web-app/ui, output is dist.
    // We need to write to the output location Bazel expects.
    // js_run_binary outs=["dist"] means it expects "dist" directory in the cwd.

    if (!fs.existsSync('dist')) {
        fs.mkdirSync('dist', { recursive: true });
    }
    fs.writeFileSync('dist/index.html', '<html><body><h1>Build Failed (Fallback)</h1></body></html>');
    fs.writeFileSync('dist/styles.css', '/* Fallback */');
    // Copy artifacts to satisfy any specific needs? 
    // But outs=["dist"] is a directory, so having content is enough.

    process.exit(1); // Exit failure to show logs
}
